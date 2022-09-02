#include <iostream>
#include <string.h>
#include <math.h>

bool is_valid_number(char * str)
{
    int i=0;
    while(str[i] != 0) 
    {
        if (str[i]<'0' || str[i]>'9')
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

    bool show_cosine = false;
    if (argc==4 && strcmp(argv[3], "c")==0)
    {
        show_cosine = true;
    }

    int sample_cnt = atoi(argv[1]);
    int bit_num = atoi(argv[2]);
    //   std::cout << "Sample Cnt = " << sample_cnt << " bit_num=" << bit_num << "\n";

    double step = 2 * M_PI / sample_cnt;
    int factor = (pow(2, bit_num) / 2) - 1;

    for (int i = 0; i < sample_cnt; i++)
    {
        double sin_value = sin(i * step) * factor;
        int int_sample = sin_value;


        std::cout << int_sample ; 
        if (show_cosine) {
            double cos_value = cos(i*step) * factor;
            int cos_int = cos_value;
            std::cout << "\t" << cos_int;
        }
        std::cout << "\n";
    }

    return 0;
}