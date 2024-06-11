#include <iostream>
#include <vector>

double IP(std::vector<double> f, std::vector<double> g){
    int df = f.size() - 1, dg = g.size() - 1;
    int d = df + dg;
    std::vector<double> h(d+1, 0);
    for (int n=0; n<=d; ++n){
        for (int m=std::max(0, n-df); m<=std::min(df, n); ++m){
            if (n-m<=dg) h.at(n) += f.at(m) * g.at(n-m);
        }
    }
    double res = 0;
    for (int n=0; n<=d; n+=2){
        res += h.at(n)/(n+1)*2; // [-1, 1] で積分
    }
    return res;
}

void regularize(std::vector<double> &f){
    double sqrIPff = std::sqrt(IP(f,f));
    for (int n=0; n<f.size(); ++n){
        f.at(n) /= sqrIPff;
    }
}

int main(){
    std::vector<double> f = {1, 2, 3, 4, 5};
    std::vector<double> g = {1, 2, 3, 4};
    std::cout << IP(f, g) << std::endl;

    int K = 15;
    std::vector<std::vector<double>> u(K+1);
    u.at(1).push_back(1.);
    regularize(u.at(1));
    for (int n=0; n<u.at(1).size(); ++n){
        std::cout << u.at(1).at(n) << ' ';
    }

    for (int k=1; k<K; ++k){
        // u.at(k).push_back(0);
        std::vector<double> v = {0};
        for (int n=0; n<u.at(k).size(); ++n){
            v.push_back(u.at(k).at(n));
        }
        u.at(k+1) = v;
        for (int i=1; i<k; ++i){
            int d = u.at(i).size()-1;
            std::vector<double> w(2*d+1, 0);
            for (int n=0; n<w.size(); ++n){
                for (int m=std::max(0, n-d); m<=std::min(d, n); ++m){
                    w.at(n) += u.at(i).at(m) * u.at(i).at(n-m);
                }
                // std::cout << w.at(n) << ' ';
            }
            // std::cout << IP(v,w) << std::endl;
            u.at(k+1).at(0) -= IP(v, w);
        }
        regularize(v);
        u.at(k+1) = v;
    }


    std::cout << "\n----------" << std::endl;
    for (int k=1; k<=K; ++k){
        for (int n=k; n<=K; ++n){
            std::cout << IP(u.at(k), u.at(n)) << ' ';
        }
        std::cout << std::endl;
    }


    return 0;
}