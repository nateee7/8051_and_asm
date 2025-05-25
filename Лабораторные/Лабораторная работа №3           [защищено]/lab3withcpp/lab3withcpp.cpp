#include <iostream>
#include <locale.h>

extern "C" int	asm_func_1(int* arr, int arr_len);


int main() {
	setlocale(LC_ALL, "Russian");

	int arr[200];
	int arr_len;
	int res = 0x123;

	std::cout << "\n\n\n\tПрограмма к лабораторной работе №3\n";
	std::cout << "\n\tЗадание по варианту №9 (№19):\n";
	std::cout << "\n\tВ массиве 16-разрядных чисел без знака найти сумму чисел с кодовой двоичной комбинацией \"1101\".";
	std::cout << "\n\tЧисло элементов массива задаётся в программе";

	std::cout << "\n\n\tВведите размер массива: ";
	std::cin >> arr_len;
	std::cout << "\n\n\tВведите значения массива:\n";

	for (int i = 0; i < arr_len; i++) {
		std::cout << "\tarr[" << i << "] = ";
		std::cin >> arr[i];
	}

	res = asm_func_1(arr, arr_len);
	std::cout << "\n\n\tПосле выполнения программы был получен ответ: " << res;

	std::cout << "\n\n\n\t";
	system("pause");

	return 0;
}