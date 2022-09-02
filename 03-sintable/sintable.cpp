#include <iostream>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{

    int sample_cnt = atoi(argv[1]);
    int bit_num = atoi(argv[2]);
    //   std::cout << "Sample Cnt = " << sample_cnt << " bit_num=" << bit_num << "\n";

    double step = 2 * M_PI / sample_cnt;
    int factor = (pow(2, bit_num) / 2) - 1;

    for (int i = 0; i < sample_cnt; i++)
    {
        double sin_value = sin(i * step) * factor;
        int int_sample = sin_value;

        std::cout << int_sample << "\n";
    }

    return 0;
}