#include <iostream>
#include <cstring>
#include <cmath>
#include <numbers>

bool is_valid_number(const char *str)
{
    auto i{0};
    while (str[i] != 0)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }

        i++;
    }

    return true;
}

struct user_data
{
    bool valid;
    std::string error_msg;
    bool show_cosine;
    int sample_cnt;
    int bit_num;
};

user_data process_user_input(int argc, char *argv[])
{
    if (argc < 3)
    {
        return user_data{false, "Invalid number of arguments."};
    }

    if (!is_valid_number(argv[1]) || !is_valid_number(argv[2]))
    {
        return user_data{false, "Invalid arguments."};
    }

    user_data return_value{
        true,
        "ok",
        argc == 4 && std::strcmp(argv[3], "c") == 0,
        std::atoi(argv[1]),
        std::atoi(argv[2]),
    };

    return return_value;
}

void create_sine_cosine_table(int sample_cnt, int bit_num, auto do_op)
{
    auto step{2 * std::numbers::pi / sample_cnt};
    auto factor{(1 << (bit_num - 1)) - 1};

    auto create_sample_function = [factor](auto radian_value, double (*sin_cos_func)(double))
    {
        auto sample_value = sin_cos_func(radian_value) * factor;
        return static_cast<int>(std::round(sample_value));
    };

    for (int i{0}; i < sample_cnt; i++)
    {
        auto radian_value = i * step;
        auto cos_value = create_sample_function(radian_value, std::cos);
        auto sin_value = create_sample_function(radian_value, std::sin);

        do_op(sin_value, cos_value);
    }
}

int main(int argc, char *argv[])
{

    auto [valid, error_msg, show_cosine, sample_cnt, bit_num] = process_user_input(argc, argv);

    if (!valid)
    {
        std::cout << error_msg << "\n";
        return -1;
    }

    create_sine_cosine_table(sample_cnt, bit_num, [show_cosine](auto sin_value, auto cos_value)
                             {
        std::cout << sin_value;
        if (show_cosine)
        {
            std::cout << "\t" << cos_value;
        }
        std::cout << "\n"; });

    return 0;
}