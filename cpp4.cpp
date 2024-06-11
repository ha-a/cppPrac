#include <iostream>
#include <vector>

class interp{
public:
    int N;
    double dx;
    double a = 25;
    std::vector<double> xn, yn;

    interp(int N){
        this->N = N;
        this->dx = 2./static_cast<double>(N-1);
        xn.resize(N);
        yn.resize(N);
    }


    double f(double x){
        return 1/(a*x*x + 1);
    }

    void make_data(){
        double x = -1;
        for (int n=0; n<N; ++n){
            xn.at(n) = x;
            yn.at(n) = f(x);
            x += dx;
        }
        return;
    }

    double fn(double x){
        double res = 0;
        for (int n=0; n<N; ++n){
            double res_n = yn.at(n);
            for (int m=0; m<N; ++m){
                if (n==m) continue;
                res_n *= (x-xn.at(m))/(xn.at(n)-xn.at(m));
            }
            res += res_n;
        }
        return res;
    }
};

int main()
{
    int N = 11;
    interp myInterp(N);
    myInterp.make_data();

    int M = 21;
    double dx = 2./static_cast<double>(M-1);
    double x = -1;
    for (int n=0; n<M; ++n){
        std::cout << x << ' ' << myInterp.f(x) << ' ' << myInterp.fn(x) << std::endl;
        x += dx;
    }
    
    return 0;
}