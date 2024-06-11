#include <iostream>
#include <cmath>

double p(double x){
    return 1.0/std::sqrt(2*M_PI) * std::exp(-x*x/2.);
}
double x2p(double x){
    return x*x * p(x);
}
double cosp(double x){
    return std::cos(x) * p(x);
}
double ex1p(double x){
    return std::max(0., std::exp(x)-1)*p(x);
}

double int_trap(double (*f)(double), double xmin, double xmax, int N){
    double dx = (xmax-xmin)/(N-1);
    double x = xmin;
    double res = 0;
    for (int n=0; n<N; ++n){
        double y = x + dx;
        res += (f(x) + f(y)) * dx / 2.;
        x = y;
    }
    return res;
}

double int_simp(double (*f)(double), double xmin, double xmax, int N){
    double dx = (xmax-xmin)/(N-1);
    double x = xmin;
    double res = 0;
    for (int n=0; n<N; ++n){
        double y = x + dx;
        res += (f(x) + 4*f(x+dx/2) + f(y)) * dx / 6.;
        x = y;
    }
    return res;
}

int main(){
    std::cout << int_simp(p, -5, 5, 1000) << std::endl;
}