#include <iostream>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <intrin.h>  // for __rdtsc function
//#include <cstdint>   // for uint64_t

#include "c_func.c"


uint64_t get_cycles();

extern "C" double   func1(double inp);
extern "C" double   func2(double inp);
extern "C" void     func3(double* inp_arr, int inp_arr_len);
extern "C" void     func4_asm_only(double* inp_arr, int inp_arr_len);
//extern "C" double c_function(double inp);

int main() {
    setlocale(LC_ALL, "Russian");

    double arr[11]/* = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }*/;
    int arr_len = 11;

    uint64_t before;
    uint64_t after;
    uint64_t total;
    uint64_t total1, total2, total3;

    std::cout << "\n\n\n\tКонсольная программа для лабораторной работы №4\n\tРаботу выполнил Игнатович В.О.\n\n";
    std::cout << "\tЗадание по варианту №19: необходимо вычислить f(x) = (tg(x) + sin(x)) / e^x.\n";
    std::cout << "\tДалее будет найдено значение данной функции на интервале[0, 1] с шагом 0.1\n";

    for (int i = 0; i < arr_len; i++)
        arr[i] = (double)i/10;



    
    before = get_cycles();
    func3(arr, arr_len);
    after = get_cycles();
    total2 = 2200;
    total1 = after - before;

    std::cout << "\n\tПосле выполнения программы был получен массив значений:\n\n";
    for (int i = 0; i < arr_len; i++) {
        //buf = func1((double)i/10);
        //buf = func2((double)i/10);
        std::cout << "\tЗначение функции при\tx = ";
        printf_s("%.1f", (float)i/10);
        std::cout << ":\t";
        printf_s("%.5f", arr[i]);
        std::cout << std::endl;
    }
    //printf("\n\tЗа время выполнения программы (C + masm) прошло машинных циклов:\t%ld \n", total);

    //printf("\n\n\tПрошло секунд: %.3f\n",
    //    ((double)(stop - start) / CLOCKS_PER_SEC));

    for (int i = 0; i < arr_len; i++)
        arr[i] = (double)i / 10;

    before = get_cycles();
    func4_asm_only(arr, arr_len);
    after = get_cycles();
    total2 += after - before;

    std::cout << "\n\tПосле выполнения программы, написанной только на masm, был получен массив значений:\n\n";
    for (int i = 0; i < arr_len; i++) {
        //buf = func1((double)i/10);
        //buf = func2((double)i/10);
        std::cout << "\tЗначение функции при\tx = ";
        printf_s("%.1f", (float)i / 10);
        std::cout << ":\t";
        printf_s("%.5f", arr[i]);
        std::cout << std::endl;
    }

    //printf("\n\n\tПрошло секунд: %.3f\n",
    //    ((double)(stop - start) / CLOCKS_PER_SEC));


    for (int i = 0; i < arr_len; i++)
        arr[i] = (double)i / 10;

    before = get_cycles();
    c_func_c_only(arr, arr_len);
    after = get_cycles();
    total3 = after - before;

    std::cout << "\n\tПосле выполнения программы, написанной только на C, был получен массив значений:\n\n";
    for (int i = 0; i < arr_len; i++) {
        //buf = func1((double)i/10);
        //buf = func2((double)i/10);
        std::cout << "\tЗначение функции при\tx = ";
        printf_s("%.1f", (float)i / 10);
        std::cout << ":\t";
        printf_s("%.5f", arr[i]);
        std::cout << std::endl;
    }

    //printf("\n\n\tПрошло секунд: %.3f\n",
    //    ((double)(stop - start) / CLOCKS_PER_SEC));




    std::cout << "\n\n\tВыполнение функций заняло:";

    printf("\n\t\tC + MASM:\t%d\tмашинных циклов\n", (int)total1);
    printf("\n\t\tMASM:\t\t%d\tмашинных циклов\n", (int)total2);
    printf("\n\t\tC:\t\t%d\tмашинных циклов\n", (int)total3);



    
    std::cout << "\n\n\n\t";
    system("pause");
}


uint64_t get_cycles() {
    //return (uint64_t)__rdtsc();     // "Read Time-Stamp Counter" instruction from "intrin.h"






    //int cpuInfo[4];         // Array to hold CPU info
    //uint64_t res;

    //__cpuid(cpuInfo, 0);    // Serialize: execute CPUID with function 0
    //res = __rdtsc();
    //return res;








    unsigned int aux;
    return __rdtscp(&aux);


}
