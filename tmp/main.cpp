#include <iostream>
#include <vector>
#include "matOperator.h"



int main()
{
    std::vector<std::vector<double>> mat1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> mat2 = {{7, 8}, {9, 10}, {11, 12}};
    std::vector<std::vector<double>> mat3 = matmul(mat2, mat1);
    printMatrix(mat3);
    std::vector<double> vec1 = {1, 2, 3};
    std::vector<double> vec2 = matmul(mat1, vec1);
    printVector(vec2);

    std::size_t N = mat3.size();
    std::vector<std::vector<bool>> pivotMat(N, std::vector<bool>(N, false));
    for (std::size_t i=0; i<N; ++i)
    {
        pivotMat[i][i] = true;
    }
    LUdecomposition(mat3,pivotMat);
    printMatrix(mat3);
    printMatrix(pivotMat);

    
    
    return 0;
}