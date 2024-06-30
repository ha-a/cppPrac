// #include "matOperator.h"
#include <vector>
#include <iomanip>

#include <iostream>
#include <vector>
// #include "matOperator.h"

template<typename T>
std::vector<std::vector<T>> makeHilbertInvMatrix(size_t N);

template<typename T>
void printMatrix(const std::vector<std::vector<T>> &inMatrix){
    for (auto &row : inMatrix)
    {
        for (auto &elem : row)
        {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
};

template<typename T>
std::vector<T> matmul(const std::vector<std::vector<T>> &inMatrix, const std::vector<T> &inVector){
    std::size_t N = inMatrix.size();
    std::size_t M = inMatrix[0].size();
    if (inVector.size() != M)
    {
        std::cerr << "Error: matrix and vector sizes do not match" << std::endl;
    }
    std::vector<T> res;
    res.reserve(N);
    for (std::size_t n=0; n<N; ++n)
    {
        res.push_back(0);
        for (std::size_t m=0; m<M; ++m)
        {
            res[n] += inMatrix[n][m] * inVector[m];
        }
    }
    return res;
};

template<typename T>
std::vector<std::vector<T>> matmul(const std::vector<std::vector<T>> &inMatrixLeft, const std::vector<std::vector<T>> &inMatrixRight){
    std::size_t N = inMatrixLeft.size();
    std::size_t M = inMatrixLeft[0].size();
    if (inMatrixRight.size() != M || inMatrixRight[0].size() != N)
    {
        std::cerr << "Error: matrix sizes do not match" << std::endl;
    }
    std::vector<std::vector<T>> res;
    res.reserve(N);
    for (std::size_t n=0; n<N; ++n)
    {
        std::vector<T> row;
        row.reserve(M);
        for (std::size_t m=0; m<M; ++m)
        {
            row.push_back(0);
            for (std::size_t l=0; l<M; ++l)
            {
                row[m] += inMatrixLeft[n][l] * inMatrixRight[l][m];
            }
        }
        res.push_back(row);
    }
    return res;
};

template<typename T>
void LUdecomp(std::vector<std::vector<T>>& inMatrix)
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

template<typename T>
std::vector<T> vecMinus(const std::vector<T> &a, const std::vector<T> &b)
{
    std::size_t N = a.size();
    std::vector<T> res(N, 0);
    for (std::size_t n=0; n<N; ++n)
    {
        res[n] = a[n] - b[n];
    }
    return res;
}

template<typename T>
std::vector<T> vecPlus(const std::vector<T> &a, const std::vector<T> &b)
{
    std::size_t N = a.size();
    std::vector<T> res(N, 0);
    for (std::size_t n=0; n<N; ++n)
    {
        res[n] = a[n] + b[n];
    }
    return res;
}

template<typename T>
T vecAbsSquared(const std::vector<T> &inVector)
{
    T res = 0;
    for (std::size_t n=0; n<inVector.size(); ++n)
    {
        res += inVector[n] * inVector[n];
    }
    return res;
}



template<typename T>
void iterativeImprovement(const std::vector<std::vector<T>> &inMatrix, const std::vector<std::vector<T>> &inMatrixLU, const std::vector<T> &inVector, std::vector<T> &inoutVector)
{
    std::size_t N = inVector.size();
    std::vector<T> residual = vecMinus(inVector,matmul(inMatrix, inoutVector));
    auto eps = vecAbsSquared(residual);
    // auto invA = makeHilbertInvMatrix<long double>(N);
    while (eps > 1e-20)
    {
        std::cout << eps << std::endl;
        forwardBackward(inMatrixLU, residual);
        // residual = matmul(invA, residual);
        inoutVector = vecPlus(inoutVector, residual);
        residual = vecMinus(inVector, matmul(inMatrix, inoutVector));
        eps = vecAbsSquared(residual);
        if(eps > 1e20) break;
    }
}

template<typename T>
std::vector<std::vector<T>> makeHilbertMatrix(size_t N)
{
    std::vector<std::vector<T>> res(N, std::vector<T>(N, 0));
    for (size_t n=0; n<N; ++n)
    {
        for (size_t m=0; m<N; ++m)
        {
            res[n][m] = 1./(n+m+1);
        }
    }
    return res;
}


int combination(const int n, const int r)
{
    if (r == 0 || r == n) return 1;
    int res = 1;
    for (int i=0; i<r; ++i)
    {
        res *= n-i;
        res /= i+1;
    }
    return res;
}

template <typename T>
std::vector<std::vector<T>> makeHilbertInvMatrix(size_t N)
{
    std::vector<std::vector<T>> res(N, std::vector<T>(N, 0));
    for (size_t n=0; n<N; ++n)
    {
        for (size_t m=0; m<N; ++m)
        {
            res[n][m] = std::pow(-1, n+m) * (n+m+1) * combination(N+n, N-m-1) * combination(N+m, N-n-1) * combination(n+m, n) * combination(n+m, m);
        }
    }
    return res;
}


template<typename T>
std::vector<std::vector<T>> LUdecompPivot(std::vector<std::vector<T>>& inMatrix)
{
    std::size_t N = inMatrix.size();
    std::vector<std::vector<T>> pivotMatrix(N, std::vector<T>(N, 0));
    for (std::size_t i=0; i<N; ++i)
    {
        pivotMatrix[i][i] = 1;
    }
    for (std::size_t i=0; i<N; ++i)
    {
        T maxElem = 0;
        std::size_t maxIndex = 0;
        for (std::size_t j=i; j<N; ++j)
        {
            if (std::abs(inMatrix[j][i]) > maxElem)
            {
                maxElem = std::abs(inMatrix[j][i]);
                maxIndex = j;
            }
        }
        if (maxIndex != i)
        {
            std::swap(inMatrix[i], inMatrix[maxIndex]);
            std::swap(pivotMatrix[i], pivotMatrix[maxIndex]);
        }
        for (std::size_t j=i+1; j<N; ++j)
        {
            inMatrix[j][i] /= inMatrix[i][i];
            for (std::size_t k=i+1; k<N; ++k)
            {
                inMatrix[j][k] -= inMatrix[j][i] * inMatrix[i][k];
            }
        }
    }
    return pivotMatrix;
};











int main()
{
    // std::vector<std::vector<double>> A{{1, 2, 4}, {2, 5, 1}, {1, 5, 3}};
    // std::vector<std::vector<double>> LU = A;
    // auto pivotMatrix = LUdecompPivot(LU);
    // printMatrix(LU);
    // printMatrix(pivotMatrix);

    size_t N = 25;
    auto A = makeHilbertMatrix<double>(N);
    // auto invA = makeHilbertInvMatrix<double>(N);
    // auto I = matmul(A, invA);
    // printMatrix(I);

    auto LU = A;
    auto P = LUdecompPivot(LU);
    // printMatrix(P);
    std::vector<double> b;
    for (int i=0; i<N; ++i) b.push_back(1);
    auto x = matmul(P, b);
    forwardBackward(LU, x);
    iterativeImprovement(matmul(P,A), LU, matmul(P,b), x);
    auto c = vecAbsSquared(vecMinus(b,matmul(A, x)));
    std::cout << std::setprecision(10);
    std::cout << c << std::endl;
}