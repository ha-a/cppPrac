#include <iostream>

class myFunc{
public:
    double a;

    myFunc(double in_a) {a = in_a;}
    
    double func(double x)
    {
        return a * x * x - 1;
    }

    double func_prime(double x)
    {
        return 2*a*x;
    }

};

double func(double x)
{
    double a = 15;
    // return a * x * x - 1;
    return x*x*x*x*x - 1;
}

double func_prime(double x)
{
    double a = func(1) + 1;
    // return 2*a*x;
    return 5*x*x*x*x;
}


double bisection(double (*f)(double), double tol)
{
    double xl = 0., xu = 1000;
    while (xu-xl>tol)
    {
        double x = (xu+xl)/2;
        if (f(xl)*f(x)>0) xl = x;
        else xu = x;
    }
    return xl;
}

double Secant(double (*f)(double), double x1, double x2, double tol){
    double f1 = f(x1), f2 = f(x2);
    while (abs(f2)>tol)
    {
        double x3 = x2 - f2*(x2-x1)/(f2-f1);
        x1 = x2; x2 = x3;
        f1 = f2; f2 = f(x2);
    }
    return x2;
}

double Newton_an(double (*f)(double), double (*df)(double), double x, double tol)
{
    while (abs(f(x))>tol)
    {
        x -= f(x)/df(x);
    }
    return x;
}

double Newton_nu(double (*f)(double), double x, double tol)
{
    while (abs(f(x))>tol)
    {
        double dx = 1e-6;
        double df = (f(x+dx/2)-f(x-dx/2))/dx;
        x -= f(x)/df;
    }
    return x;
}


template<class Fn>
double Newton_nu_2(Fn f, double x, double tol) {
    while (abs(f(x))>tol)
    {
        double dx = 1e-6;
        double df = (f(x+dx/2)-f(x-dx/2))/dx;
        x -= f(x)/df;
    }
    return x;
}

int main()
{
    double tol = 1e-6;


    double root = bisection(func, tol);
    std::cout << "Root: " << root << std::endl;
    // root = Secant(func, 0, 1000, tol);
    // std::cout << "Root: " << root << std::endl;
    // root = Newton_an(func, func_prime, 1000, tol);
    // std::cout << "Root: " << root << std::endl;
    // root = Newton_nu(func, 1000, tol);
    // std::cout << "Root: " << root << std::endl;
    root = Newton_nu_2(func, 1000, tol);
    std::cout << "Root: " << root << std::endl;
    return 0;
}