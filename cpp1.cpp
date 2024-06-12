#include <iostream>
#include <string>
#include <iomanip>


#include <stdio.h>
#include <float.h>

using target_type = float;
enum class x_type {float_, double_};
enum class base_type {binary, hex};

std::string binary(target_type& x, base_type bs){
    std::string str = "0x";
    target_type base = 0;
    switch(bs){
        case base_type::binary:
            str = "0b"; base = 2; break;
        case base_type::hex:
            str = "0x"; base = 16; break;
    }

    target_type v = 1;
    while (v<=x && !std::isinf(v*base)){
        // std::cout << v << std::endl;
        v *= base;
    }
    bool flag = true;
    while (x>0||v>=1){
        // std::cout << v << std::endl;
        if (v<1 && flag){
            if (str.size()==2) str += "0";
            str += ".";
            flag = false;
        }
        if (x / v >= 1){
            int s = static_cast<int>(x/v);
            x -= s * v;
            switch (s){
                case 10:
                    str += "a"; break;
                case 11:
                    str += "b"; break;
                case 12:
                    str += "c"; break;
                case 13:
                    str += "d"; break;
                case 14:
                    str += "e"; break;
                case 15:
                    str += "f"; break;
                default:
                    str += std::to_string(s);
            }
        } else {
            if (str.size()!=2) str += "0";
        }
        v /= base;
    }
    return str;
}

target_type minimum1(){
    target_type x = 1.;
    while (x/2!=0)
    {
        x /= 2;
        // printf("x = %e\n", x);
    }
    target_type u = 0.;
    printf("x = %e\n", x);
    while (x!=u){
        target_type m = (x+u)/2.;
        printf("%e, %e, %e\n", x, u, m);
        if (1+m==1) x = m;
        else u = m;
        printf("x = %e\n", x);
    }
    return u;
}

target_type times2(std::string){
    target_type res = 0.;
    
}

int main(){
    std::string x_str = "123456789";
    target_type x = static_cast<target_type>(std::stold(x_str));
    auto tmp = binary(x, base_type::hex);
    std::cout << tmp << std::endl;
    std::cout << x_str << ' ';
    std::cout << std::fixed << std::setprecision(0) << std::stold(tmp) << std::endl;
    // binary(x);
    
    auto y = minimum1();
    std::cout << ((y==0)?1:0) << std::endl;
    // std::cout << std::fixed << std::setprecision(100) << y << std::endl;
    printf("y = %e\n", y);
    printf("FLT_MIN = %e\n", FLT_MIN);  

    return 0;
}