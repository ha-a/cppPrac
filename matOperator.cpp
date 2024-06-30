#include <iostream>
#include <vector>
#include "matOperator.h"



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
