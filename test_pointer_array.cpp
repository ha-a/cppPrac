#include <iostream>
#include <cmath>

int main() {
    float a = 0.02f;
    float b = 802.0f;
    float c = 1.01f;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        std::cout << "No real roots." << std::endl;
    } else {
        float sqrt_discriminant = std::sqrt(discriminant);

        // 2a
        float two_a = 2 * a;

        // 数値的に安定な計算方法
        float x1, x2;
        if (b > 0) {
            x1 = (-b - sqrt_discriminant) / two_a;
            x2 = c / (a * x1);
        } else {
            x1 = (-b + sqrt_discriminant) / two_a;
            x2 = c / (a * x1);
        }

        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;

        std::cout << x1+x2 << ' ' << b/a << std::endl;
        std::cout << x1*x2 << ' ' << c/a << std::endl;
    }

    return 0;
}
