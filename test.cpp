#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

void makeHilbert(std::vector<std::vector<double>> &A){
    int N = A.size();
    for (int n=0; n<N; ++n){
        for (int m=0; m<N; ++m){
            A[n][m] = 1.0 / (n + m + 1);
        }
    }
}

std::vector<double> matVecMul(const std::vector<std::vector<double>> &A, const std::vector<double> &x) {
    int N = A.size();
    std::vector<double> b(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            b[i] += A[i][j] * x[j];
        }
    }
    return b;
}

double dot(const std::vector<double> &a, const std::vector<double> &b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

std::vector<double> vecAdd(const std::vector<double> &a, const std::vector<double> &b, double alpha = 1.0) {
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + alpha * b[i];
    }
    return result;
}

std::vector<double> vecSub(const std::vector<double> &a, const std::vector<double> &b) {
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

std::vector<double> scalarVecMul(const std::vector<double> &a, double scalar) {
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] * scalar;
    }
    return result;
}

int main() {
    int N = 14;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0));
    makeHilbert(A);
    std::vector<double> b(N, 1);
    std::vector<double> x(N, 0);
    
    std::vector<double> r = vecSub(b, matVecMul(A, x));
    std::vector<double> p = r;
    double rsold = dot(r, r);
    double tolerance = 1e-14;
    int max_iterations = 100;
    
    for (int i = 0; i < max_iterations; ++i) {
        std::vector<double> Ap = matVecMul(A, p);
        double alpha = rsold / dot(p, Ap);
        x = vecAdd(x, p, alpha);
        r = vecSub(r, scalarVecMul(Ap, alpha));
        double rsnew = dot(r, r);
        if (sqrt(rsnew) < tolerance) {
            std::cout << "Converged after " << i + 1 << " iterations with error " << sqrt(rsnew) << std::endl;
            break;
        }
        p = vecAdd(r, p, rsnew / rsold);
        rsold = rsnew;
        std::cout << "Error after iteration " << i + 1 << ": " << sqrt(rsnew) << std::endl;
    }

    return 0;
}
