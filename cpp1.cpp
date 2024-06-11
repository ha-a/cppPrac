#include <iostream>
#include <string>

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
            str += "0";
        }
        v /= base;
    }
    return str;
}

int main(){
    target_type x = 0x7FFFFFFF;
    std::cout << binary(x, base_type::hex) << std::endl;
    // binary(x);
    return 0;
}