#include <iostream>
#include <locale.h>
#include "c_func.c"

extern "C" double   func1(double inp);
extern "C" double   func2(double inp);
extern "C" void     func3(double* inp_arr, int inp_arr_len);
//extern "C" double c_function(double inp);

int main() {
    setlocale(LC_ALL, "Russian");

    double arr[11]/* = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }*/;
    int arr_len = 11;

    std::cout << "\n\n\n\tКонсольная программа для лабораторной работы №4\n\tРаботу выполнил Игнатович В.О.\n\n";
    std::cout << "\tЗадание по варианту №19: необходимо вычислить f(x) = (tg(x) + sin(x)) / e^x.\n";
    std::cout << "\tДалее будет найдено значение данной функции на интервале[0, 1] с шагом 0.1\n";

    for (int i = 0; i < arr_len; i++)
        arr[i] = (double)i/10;
    func3(arr, arr_len);

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

    
    std::cout << "\n\n\n\t";
    system("pause");
}
