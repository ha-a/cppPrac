#include <iostream>
#include <vector>
#include "matOperator.h"


std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>> &inMat1, const std::vector<std::vector<double>> &inMat2)
{
    std::size_t col1 = inMat1[0].size();
    std::size_t row1 = inMat1.size();
    std::size_t col2 = inMat2[0].size();
    std::size_t row2 = inMat2.size();
    if (col1 != row2)
    {
        std::cerr << "Error: The number of columns of the first matrix must be equal to the number of rows of the second matrix." << std::endl;
        exit(1);
    }
    std::vector<std::vector<double>> outMat;
    outMat.reserve(row1);
    for (std::size_t r=0; r<row1; ++r)
    {
        std::vector<double> rowVec;
        rowVec.reserve(col2);
        for (std::size_t c=0; c<col2; ++c)
        {
            double sum = 0;
            for (std::size_t n=0; n<col1; ++n)
            {
                sum += inMat1[r][n] * inMat2[n][c];
            }
            rowVec.push_back(sum);
        }
        outMat.push_back(rowVec);
    }
    return outMat;    
};

std::vector<double> matmul(const std::vector<std::vector<double>> &inMat, const std::vector<double> &inVec)
{
    std::size_t colMat = inMat[0].size();
    std::size_t rowMat = inMat.size();
    std::size_t rowVec = inVec.size();
    if (colMat != rowVec)
    {
        std::cerr << "Error: The number of columns of the first matrix must be equal to the number of rows of the vector." << std::endl;
        exit(1);
    }
    std::vector<double> outVec;
    outVec.reserve(rowMat);
    for (std::size_t r=0; r<rowMat; ++r)
    {
        double sum = 0;
        for (std::size_t n=0; n<colMat; ++n)
        {
            sum += inMat[r][n] * inVec[n];
        }
        outVec.push_back(sum);
    }
    return outVec;

};

void LUdecomposition(std::vector<std::vector<double>> &inoutMatrix)
{
    int N = inoutMatrix.size();
    for (int n=0; n<N; ++n)
    {
        for (int m=0; m<N; ++m)
        {
            if (m<n)
            {
                for (int k=0; k<m; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
                inoutMatrix.at(n).at(m) /= inoutMatrix.at(m).at(m);
            } 
            else 
            {
                for (int k=0; k<n; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
            }
        }
    }
};

void LUdecomposition3(std::vector<std::vector<double>> &inoutMatrix)
{
    int N = inoutMatrix.size();
    for (int n=0; n<N; ++n)
    {
        for (int m=std::max(0,n-1); m<std::min(N,n+1); ++m)
        {
            if (m<n)
            {
                for (int k=std::max(0,n-1); k<m; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
                inoutMatrix.at(n).at(m) /= inoutMatrix.at(m).at(m);
            } 
            else 
            {
                for (int k=std::max(0,n-1); k<n; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
            }
        }
    }
};

void LUdecomposition(std::vector<std::vector<double>> &inoutMatrix, std::vector<std::vector<bool>> &inoutPivotMat)
{
    int N = inoutMatrix.size();
    for (int n=0; n<N; ++n)
    {
        std::size_t p = 0;
        double max_elem = 0;
        for (std::size_t m=n; m<N; ++m)
        {
            if (std::abs(inoutMatrix[m][n])>max_elem)
            {
                max_elem = std::abs(inoutMatrix[m][n]);
                p = m;
            }
        }
        if (p!=n)
        {
            std::swap(inoutMatrix[n], inoutMatrix[p]);
            std::swap(inoutPivotMat[n], inoutPivotMat[p]);
        }
        for (int m=0; m<N; ++m)
        {
            if (m<n)
            {
                for (int k=0; k<m; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
                inoutMatrix.at(n).at(m) /= inoutMatrix.at(m).at(m);
            } 
            else 
            {
                for (int k=0; k<n; ++k)
                {
                    inoutMatrix.at(n).at(m) -= inoutMatrix.at(n).at(k) * inoutMatrix.at(k).at(m);
                }
            }
        }
    }
};


