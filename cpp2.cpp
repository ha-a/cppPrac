/*
( -b + sqrt(b^2 - 4ac) ) / 2a
( -b^2 + b^2 - 4ac) / 2a / (b+sqrt(b^2-4ac))
*/


#include <iostream>
#include <cmath>

int main()
{
    float ans = 0;
    for (int k=1; k<=14096; ++k) ans += 1.0/k/k;
    std::cout << ans << ' ';
    ans = 0;
    for (int k=14096; k>=1; --k) ans += 1.0/k/k;
    std::cout << ans << std::endl << std::endl;

    double a = 0.02, b = 802, c = 1.01;
    double x = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
    std::cout << x << ' ';
    ans = a*x*x + b*x + c;
    std::cout << ans << std::endl;
    x = (-b - std::sqrt(b*b - 4*a*c))/(2*a);
    std::cout << x << ' ';
    ans = a*x*x + b*x + c;
    std::cout << ans << std::endl;

    float aa = 0.02, bb = 802, cc = 1.01;
    float xx = - 4 * aa * cc;
    float yy = bb + std::sqrt(bb*bb - 4*aa*cc);
    xx /= yy * 2 * aa;
    std::cout << xx << ' ' << aa*xx*xx + bb*xx + cc << std::endl;

    return 0;
}