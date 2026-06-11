#include <windows.h>
#include <iostream>
#include "solution.h"

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "Rus");

	while (true) {
		std::cout << "----------------- MENU -----------------" << std::endl;
		std::cout << "1) Ввод параметров вручную через консоль" << std::endl;
		std::cout << "2) Загрузка данных из файла input.txt" << std::endl;
		std::cout << "3) Выход из программы" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "Выберите действие (1-3): ";

		int choice = ReadSafeInt(1, 3);

		if (choice == 1) {
			HandleManualInput();
		}
		else if (choice == 2) {
			HandleFileInput();
		}
		else if (choice == 3) {
			std::cout << "\nВыход из программы. До свидания!\n";
			break;
		}

		std::cout << "\nНажмите Enter, чтобы вернуться в меню...";
		std::cin.get();
	}

	return 0;
}