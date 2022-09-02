#include <iostream>
#include <cstring>
#include <cmath>
#include <numbers>

bool is_valid_number(const char * str)
{
    auto i {0};
    while(str[i] != 0) 
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }

        i++;
    }

    return true;
}


int main(int argc, char *argv[])
{
    if (argc<3) {
        std::cout << "Invalid number of arguments!\n";
        return -1;
    }

    if (!is_valid_number(argv[1]) || !is_valid_number(argv[2]))
    {
        std::cout << "Invalid arguments!\n";
        return -1;        
    }

    auto show_cosine {argc==4 && std::strcmp(argv[3], "c")==0};

    auto sample_cnt { std::atoi(argv[1])};
    auto bit_num { std::atoi(argv[2])};
    auto step { 2 * std::numbers::pi / sample_cnt};
    auto factor { (1 << (bit_num-1))-1};

    for (int i = 0; i < sample_cnt; i++)
    {
        auto sin_value {std::sin(i * step) * factor};
        auto int_sample {static_cast<int>(sin_value)};


        std::cout << int_sample ; 
        if (show_cosine) {
            auto cos_value {std::cos(i*step) * factor};
            auto cos_int {static_cast<int>(cos_value)};
            std::cout << "\t" << cos_int;
        }
        std::cout << "\n";
    }

    return 0;
}