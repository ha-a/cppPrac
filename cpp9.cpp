#include <iostream>
#include <vector>

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

void LUsolve(std::vector<std::vector<double>> &A, std::vector<double> &b){
    LU(A);
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

int main(){
    int N = 5;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0));
    for (int n=0; n<N; ++n){
        for (int m=0; m<N; ++m){
            A.at(n).at(m) = 1./(n+m+1);
        }
    }
    auto LU = A;
    // LU(A);
    // for (int i=0; i<A.size(); ++i){
    //     for (int j=0; j<A.at(i).size(); ++j){
    //         std::cout << A.at(i).at(j) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    std::vector<double> b(N, 1);
    std::vector<double> x = b;
    LUsolve(LU, x);
    for (int i=0; i<x.size(); ++i){
        std::cout << x.at(i) << " ";
    }
    std::cout << std::endl;
    double res = 0;
    for (int n=0; n<N; ++n){
        double tmp = -b.at(n);
        for (int m=0; m<N; ++m){
            tmp += A.at(n).at(m) * x.at(m);
        }
        res += tmp * tmp;
    }
    res = sqrt(res);
    std::cout << res << std::endl;
}