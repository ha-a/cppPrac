#pragma once

#include <vector>

template<typename T>
void printMatrix(std::vector<std::vector<T>> &inMatrix);

template<typename T>
std::vector<T> matmul(std::vector<std::vector<T>> &inMatrix, std::vector<T> &inVector);

template<typename T>
std::vector<std::vector<T>> matmul(std::vector<std::vector<T>> &inMatrixLeft, std::vector<std::vector<T>> &inMatrixRight);

template<typename T>
void LUdecomp(std::vector<std::vector<T>>& inMatrix);
