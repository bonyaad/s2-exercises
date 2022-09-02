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

    for (int i{0}; i < sample_cnt; i++)
    {
        auto sin_value{std::sin(i * step) * factor};
        auto int_sample{static_cast<int>(std::round(sin_value))};

        auto cos_value{std::cos(i * step) * factor};
        auto cos_int{static_cast<int>(std::round(cos_value))};

        do_op(int_sample, cos_int);
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