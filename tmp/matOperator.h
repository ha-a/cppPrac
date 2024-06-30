#pragma once

#include <vector>

template <typename T>
void printMatrix(const std::vector<std::vector<T>> &inMatrix)
{
    for (auto row : inMatrix)
    {
        for (auto elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
void printVector(const std::vector<T> &inVector)
{
    for (auto elem : inVector)
    {
        std::cout << elem << std::endl;
    }
};

std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>> &inMat1, const std::vector<std::vector<double>> &inMat2);
std::vector<double> matmul(const std::vector<std::vector<double>> &inMat, const std::vector<double> &inVec);
void LUdecomposition(std::vector<std::vector<double>> &inoutMatrix);
void LUdecomposition(std::vector<std::vector<double>> &inoutMatrix, std::vector<std::vector<bool>> &inoutPivotMat);