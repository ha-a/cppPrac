#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

namespace
{
    double targetFunction(double inX)
    {
        double a = 25.;
        return 1. / (a*inX*inX + 1);
    }
    std::vector<std::pair<double, double>> makeData(int inDataNum)
    {
        double dx = 2. / static_cast<double>(inDataNum-1);
        double x = -1;
        std::vector<std::pair<double, double>> outData;
        outData.reserve(inDataNum);
        for (int n=0; n<inDataNum; ++n)
        {
            auto y = targetFunction(x);
            outData.push_back(std::make_pair(x, y));
            x += dx;
        }
        return outData;
    }
    std::vector<std::pair<double, double>> makeData(const std::vector<double> &inDataX)
    {
        std::vector<std::pair<double, double>> outData;
        for (auto x : inDataX)
        {
            auto y = targetFunction(x);
            outData.push_back(std::make_pair(x, y));
        }
        return outData;
    }
    double interpLagrange(const std::vector<std::pair<double, double>> &inData, double inX)
    {
        double res = 0;
        for (auto &data : inData)
        {
            double resN = data.second;
            for (auto &dataM : inData)
            {
                if (data == dataM) continue;
                resN *= (inX - dataM.first) / (data.first - dataM.first);
            }
            res += resN;
        }
        return res;
    }
}

struct SparseMatrix
{
    std::vector<double> m_data, m_row, m_col;
    SparseMatrix(std::vector<double> &inData, std::vector<double> &inRow, std::vector<double> &inCol)
    {
        m_data = inData;
        m_row = inRow;
        m_col = inCol;
    }
};

class InterpSpline
{
private:
    std::vector<std::pair<double, double>> data;
    std::vector<double> a, b, c, d, h;

    void LUdecomp(std::vector<std::vector<double>>& inMatrix)
    {
        std::size_t N = inMatrix.size();
        for (std::size_t i=0; i<N; ++i)
        {
            for (std::size_t j=0; j<N; ++j)
            {
                for (std::size_t k=0; k<N; ++k)
                {
                    if (k<std::min(i,j))
                    {
                        inMatrix[i][j] -= inMatrix[i][k] * inMatrix[k][j];
                    }
                }
                if (i>j)
                {
                    inMatrix[i][j] /= inMatrix[j][j];
                }
            }
        }
    };

    void LUdecomp(SparseMatrix& inMatrix)
    {
        std::size_t Nrow = *std::max_element(inMatrix.m_row.begin(), inMatrix.m_row.end());
        std::size_t Ncol = *std::max_element(inMatrix.m_col.begin(), inMatrix.m_col.end());
        std::size_t N    = std::max(Nrow, Ncol);

    };

    template<typename T>
    void forwardBackward(const std::vector<std::vector<T>> &inMatrix, std::vector<T> &inoutVector)
    {
        std::size_t N = inoutVector.size();
        for (std::size_t n=0; n<N; ++n)
        {
            for (std::size_t m=0; m<n; ++m)
            {
                inoutVector[n] -= inMatrix[n][m] * inoutVector[m];
            }
        }
        for (int n=N-1; n>=0; --n) // n が -1 になったときにループを抜けるので，n は負の値になり得なくてはならない => int 型が適切
        {
            for (int m=N-1; m>n; --m)
            {
                inoutVector[n] -= inMatrix[n][m] * inoutVector[m];
            }
            inoutVector[n] /= inMatrix[n][n];
        }
    }

public:
    InterpSpline(const std::vector<std::pair<double, double>> &inData)
    {
        data = inData;
        size_t N = inData.size() - 1;
        std::vector<std::vector<double>> Amat(N+1, std::vector<double>(N+1, 0));
        a.reserve(N); b.reserve(N+1); c.reserve(N); d.reserve(N+1); h.reserve(N);
        
        for (size_t n=0; n<=N; ++n)
        {
            d.push_back(inData[n].second);
            if (n==0) 
            {
                h.push_back(inData[n+1].first - inData[n].first);
                Amat[n][n] = 1;
                b.push_back(0);
            }
            else if (n==N)
            {
                Amat[n][n] = 1;
                b.push_back(0);
            } 
            else 
            {
                h.push_back(inData[n+1].first - inData[n].first);
                Amat[n][n-1] = inData[n].first - inData[n-1].first;
                Amat[n][n+1] = inData[n+1].first - inData[n].first;
                Amat[n][n]   = 2*(Amat[n][n-1] + Amat[n][n+1]);
                auto bi = -(inData[n].second - inData[n-1].second) / (inData[n].first - inData[n-1].first);
                bi += (inData[n+1].second - inData[n].second) / (inData[n+1].first - inData[n].first);
                b.push_back(3*bi);
            }
        }
        LUdecomp(Amat);
        forwardBackward(Amat, b);
        for (size_t n=0; n<N; ++n)
        {
            a.push_back((b[n+1] - b[n]) / (3*h[n]));
            c.push_back((d[n+1]-d[n])/h[n] - h[n]*(b[n+1]+2*b[n])/3);
        }
    }

    double operator()(double inX)
    {
        auto index = findIndex(inX);
        auto xn = data[index].first;
        double y = 0;
        y += d[index];
        y += c[index] * (inX - xn);
        y += b[index] * (inX - xn) * (inX - xn);
        y += a[index] * (inX - xn) * (inX - xn) * (inX - xn);
        return y;
    }

    std::size_t findIndex(double inX)
    {
        std::size_t index_u = data.size()-1, index_l = 0;
        while (index_u-index_l>1)
        {
            auto index_m = (index_u + index_l) / 2;
            if (data[index_m].first < inX)
            {
                index_l = index_m;
            }
            else
            {
                index_u = index_m;
            }
        }
        return index_l;
    }
};


int main()
{
    std::ofstream ofs_csv_file("output.csv");
    auto data = makeData(5);
    InterpSpline spline(data);
    ofs_csv_file << "x,y" << std::endl;
    for (std::size_t n=0; n<101; ++n)
    {
        auto x = -1 + 0.02*n;
        ofs_csv_file << x << ',' << spline(-1 + 0.02*n) << std::endl;
    }
    ofs_csv_file.close();
    // std::cout << data[1].first << std::endl;
    return 0;
}