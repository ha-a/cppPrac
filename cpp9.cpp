#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <time.h>

#include "test.h"







template<typename T>
void printMat(std::vector<std::vector<T>> &A);

void LU(std::vector<std::vector<double>> &A){
    int N = A.size();
    for (int n=0; n<N; ++n){
        for (int m=0; m<N; ++m){
            if (m<n){
                for (int k=0; k<m; ++k){
                    A.at(n).at(m) -= A.at(n).at(k) * A.at(k).at(m);
                }
                A.at(n).at(m) /= A.at(m).at(m);
            } else {
                for (int k=0; k<n; ++k){
                    A.at(n).at(m) -= A.at(n).at(k) * A.at(k).at(m);
                }
            }
        }
    }
}
void LU_decomp(std::vector<std::vector<double>> &mat){
    auto A = mat;
    int N = A.size();
    std::vector<std::size_t> p{0,1,2};
    std::vector<std::size_t> ind{0,0,0};
    do{
        // std::cout << p[0] << p[1] << p[2] << std::endl;
        A = mat;
        clock_t t_start = clock();
        for (ind[p[0]]=0; ind[p[0]]<N; ++ind[p[0]]){
            for (ind[p[1]]=0; ind[p[1]]<N; ++ind[p[1]]){
                for (ind[p[2]]=0; ind[p[2]]<N; ++ind[p[2]]){
                    if ((ind[0]>ind[1]&&ind[1]>ind[2])||(ind[0]<=ind[1]&&ind[0]>ind[2])){
                        A[ind[0]][ind[1]] -= A[ind[0]][ind[2]] * A[ind[2]][ind[1]];
                    }

                    if (ind[0]>ind[1]){
                        A[ind[0]][ind[1]] /= A[ind[1]][ind[1]];
                    } 
                }
            }
        }
        clock_t t_end = clock();
        const double calc_time = static_cast<double>(t_end - t_start) / CLOCKS_PER_SEC * 1000.;
        std::cout << "calc_time: " << calc_time << "ms" << std::endl;
        // printMat(A);
        std::cout << "--------" << std::endl;
    } while (std::next_permutation(p.begin(), p.end()));
}

void LUsolve(std::vector<std::vector<double>> &A, std::vector<double> &b){
    
    int N = A.size();
    for (int n=0; n<N; ++n){
        for (int m=0; m<n; ++m){
            b.at(n) -= A.at(n).at(m) * b.at(m);
        }
    }
    for (int n=N-1; n>=0; --n){
        for (int m=N-1; m>n; --m){
            b.at(n) -= A.at(n).at(m) * b.at(m);
        }
        b.at(n) /= A.at(n).at(n);
    }
}

std::vector<double> matvecmul(std::vector<std::vector<double>> &A, std::vector<double> &x){
    int N = A.size();
    std::vector<double> y(N, 0);
    for (int n=0; n<N; ++n){
        y.at(n) = 0;
        for (int m=0; m<N; ++m){
            y.at(n) += A.at(n).at(m) * x.at(m);
        }
    }
    return y;
}
template<typename T>
std::vector<std::vector<T>> matmul(std::vector<std::vector<T>> &A, std::vector<std::vector<T>> &B)
{
    size_t N = A.size();
    std::vector<std::vector<T>> res(N, std::vector<T>(N, 0));
    for (size_t n=0; n<N; ++n){
        for (size_t m=0; m<N; ++m){
            for (size_t k=0; k<N; ++k){
                res[n][m] += A[n][k] * B[k][m];
            }
        }
    }
    return res;
}
template<typename T>
std::vector<T> matmul(std::vector<std::vector<T>> &A, std::vector<T> &b)
{
    size_t N = A.size();
    std::vector<T> res(N, 0);
    for (size_t n=0; n<N; ++n){
        for (size_t m=0; m<N; ++m){
            res[n] += A[n][m] * b[m];
        }
    }
    return res;
}
template<typename T>
std::vector<T> vecMinus(std::vector<T> &a, std::vector<T> &b){
    size_t N = a.size();
    std::vector<T> res(N, 0);
    for (size_t n=0; n<N; ++n){
        res[n] = a[n] - b[n];
    }
    return res;
}
template<typename T>
std::vector<T> vecPlus(std::vector<T> &a, std::vector<T> &b){
    size_t N = a.size();
    std::vector<T> res(N, 0);
    for (size_t n=0; n<N; ++n){
        res[n] = a[n] + b[n];
    }
    return res;
}

template<typename T>
T vecAbs(std::vector<T> &a){
    T res = 0;
    for (size_t n=0; n<a.size(); ++n){
        res += a[n] * a[n];
    }
    return sqrt(res);
}

void preciser(std::vector<std::vector<double>> &A, std::vector<std::vector<double>> &invA, std::vector<double> &b, std::vector<double> &x, double tol){
    // auto xn = x;
    size_t N = x.size();
    auto err = matmul(A, x);
    err = vecMinus(b, err);

    do {
        auto y = matmul(invA, err);
        x = vecPlus(x, y);
        err = matmul(A, x);
        err = vecMinus(b, err);
    } while (vecAbs(err) > tol);
}

int nCk(int n, int k){
    if (n<=k) return 1;
    int res = 1;
    for (int i=n; i>n-k; --i){
        res *= i;
    }
    for (int i=1; i<=k; ++i){
        res /= i;
    }
    return res;
}
void makeHilbert(std::vector<std::vector<double>> &A){
    int N = A.size();
    for (int n=0; n<N; ++n){
        for (int m=0; m<N; ++m){
            A.at(n).at(m) = 1./(n+m+1);
        }
    }
}
void makeInvHilbert(std::vector<std::vector<double>> &A){
    int N = A.size();
    for (int n=1; n<=N; ++n){
        for (int m=1; m<=N; ++m){
            A.at(n-1).at(m-1) = std::pow(-1, n+m) * (n+m-1) * nCk(N+n-1, N-m) * nCk(N+m-1, N-n) * nCk(n+m-2, n-1) * nCk(n+m-2, n-1);
        }
    }
}

template<typename T>
void printMat(std::vector<std::vector<T>> &A){
    for (int n=0; n<A.size(); ++n){
        for (int m=0; m<A.at(n).size(); ++m){
            std::cout << A.at(n).at(m) << " ";
        }
        std::cout << std::endl;
    }
}
template<typename T>
void printMat(std::vector<T> &A){
    for (int n=0; n<A.size(); ++n){
        std::cout << A.at(n) << " ";
    }
    std::cout << std::endl;
}


#include <random>

int main(){
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());
    std::uniform_int_distribution<> dist(0, 9);
    int N = 400;
    // std::vector<std::vector<double>> A{{2,5,1},{1,5,3},{1,2,4}};
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0));
    for (std::size_t n=0; n<N; ++n){
        for (std::size_t m=0; m<N; ++m){
            A.at(n).at(m) = dist(engine);
        }
    }
    // printMat(A);
    
    LU_decomp(A);
    //  
    // int N = 20;
    // std::vector<std::vector<double>> A(N, std::vector<double>(N, 0)), invA(N, std::vector<double>(N, 0));
    // makeHilbert(A);
    // makeInvHilbert(invA);
    // auto A0 = A;

    // std::vector<double> b(N, 1);
    // for (int n=1; n<=N; ++n) b[n-1] = N-n;
    // std::vector<double> x = b;
    // LU(A);
    // // printMat(A);
    // LUsolve(A, x);
    // // printMat(A);
    // auto err = matmul(A0, x);
    // // printMat(err);
    // err = vecMinus(b, err);
    // // printMat(err);
    // std::cout << vecAbs(err) << std::endl;

    // // printMat(x);

    // // auto y = matmul(invA, b);
    // // auto c = matmul(A, y);
    // // printMat(c);

    // // auto A0 = A;
    // // printMat(A0);
    // for (int k=0; k<100; ++k){
    //     // A = A0;
    //     LUsolve(A, err);
    //     // printMat(err);
    //     x = vecPlus(x, err);
    //     err = matmul(A0, x);
    //     err = vecMinus(b, err);
    //     std::cout << vecAbs(err) << std::endl;
    // }
    // // printMat(b);
    // // while (true){
    //     // auto y = matmul(invA, err);
    //     // x = vecPlus(x, y);
    //     // err = matmul(A, x);
    //     // err = vecMinus(b, err);
    //     // // printMat(err);
    //     // std::cout << vecAbs(err) << std::endl;
    // // }

    // // printMat(invA);

    // // preciser(A, invA, b, x, 1e-20);
    // // err = matmul(A, x);
    // // err = vecMinus(b, err);
    // // printMat(x);
    // // std::cout << vecAbs(err) << std::endl;
}