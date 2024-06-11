#include <iostream>
#include <cmath>

double f(double x){
    return std::exp(x);
}
double df(double x, double dx){
    return (f(x+dx)-f(x))/dx;
}
double dfm(double x, double dx){
    return (f(x+dx/2)-f(x-dx/2))/dx;
}

int main(){
    for (int k=1; k<=16; ++k){
        double dx = std::pow(10, -k);
        std::cout << f(1) << ' ' << dx << ' ' << df(1, dx) << ' ' << dfm(1, dx) << std::endl;
    }
    return 0;    
}