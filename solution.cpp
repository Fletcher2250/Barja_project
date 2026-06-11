#include "solution.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

std::string RunBargeSimulation(int n, int k, int p,
	const std::vector<Command>& commands) {

	// Создаем K+1 стеков, чтобы использовать номера отсеков 1..K напрямую
	MyStack<int>* compartments = new MyStack<int>[k + 1];
	long long current_barrels = 0;
	long long max_barrels = 0;
	bool error_flag = false;

	try {
		for (int i = 0; i < n; i++) {
			const Command& cmd = commands[i];

			if (cmd.compartment < 1 || cmd.compartment > k) {
				error_flag = true;
				break;
			}

			if (cmd.type == '+') {
				compartments[cmd.compartment].Push(cmd.fuel_type);
				current_barrels++;

				if (current_barrels > p) {
					error_flag = true;
					break;
				}
				if (current_barrels > max_barrels) {
					max_barrels = current_barrels;
				}
			}
			else if (cmd.type == '-') {
				// Проверка на пустоту и соответствие типа топлива до извлечения
				if (compartments[cmd.compartment].IsEmpty() ||
					compartments[cmd.compartment].Top() != cmd.fuel_type) {
					error_flag = true;
					break;
				}
				compartments[cmd.compartment].Pop();
				current_barrels--;
			}
		}
	}
	catch (const std::underflow_error& e) {
		error_flag = true;
	}

	// Фиксация ошибки, если после прохождения всех доков баржа не стала пуста
	if (current_barrels != 0) {
		error_flag = true;
	}

	delete[] compartments;

	if (error_flag) {
		return "Error";
	}
	return std::to_string(max_barrels);
}

int ReadSafeInt(int min_val, int max_val) {
	int num;
	while (true) {
		if (std::cin >> num) {
			if (num >= min_val && num <= max_val) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return num;
			}
		}
		std::cout << "Неверный ввод! Нужно число от " << min_val << " до "
			<< max_val << ".\nПовторите ввод: ";

		// Сбрасываем флаг ошибки и очищаем буфер ввода, если пользователь ввел буквы
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void HandleManualInput() {
	std::cout << "\n--- Ручной ввод данных ---" << std::endl;

	std::cout << "Введите количество доков N (1..100000): ";
	int n = ReadSafeInt(1, 100000);

	std::cout << "Введите количество отсеков K (1..100000): ";
	int k = ReadSafeInt(1, 100000);

	std::cout << "Введите лимит бочек P (1..100000): ";
	int p = ReadSafeInt(1, 100000);

	std::vector<Command> commands;
	std::cout << "Введите " << n
		<< " строк с командами (формат: + 1 2 или - 1 2):" << std::endl;

	for (int i = 0; i < n; i++) {
		std::string line;
		std::getline(std::cin, line);

		std::stringstream ss(line);
		char type;
		int comp, fuel;

		if (!(ss >> type >> comp >> fuel) || (type != '+' && type != '-')) {
			std::cout << "Ошибка в формате строки! Симуляция прервана." << std::endl;
			return;
		}
		commands.push_back({ type, comp, fuel });
	}

	std::string ans = RunBargeSimulation(n, k, p, commands);
	std::cout << "\nРезультат симуляции: " << ans << "\n";
}

void HandleFileInput() {
	std::cout << "\n--- Чтение из input.txt ---" << std::endl;
	std::ifstream file("input.txt");

	if (!file.is_open()) {
		std::cout << "Ошибка: Не удалось открыть файл input.txt!\n";
		return;
	}

	int n, k, p;
	if (!(file >> n >> k >> p)) {
		std::cout << "Ошибка: неверный заголовок в файле (N, K, P).\n";
		file.close();
		return;
	}

	std::vector<Command> commands;
	char type;
	int comp, fuel;

	for (int i = 0; i < n; i++) {
		if (!(file >> type >> comp >> fuel)) {
			std::cout << "Ошибка: в файле не хватает строк или формат нарушен.\n";
			file.close();
			return;
		}
		commands.push_back({ type, comp, fuel });
	}
	file.close();

	std::string ans = RunBargeSimulation(n, k, p, commands);
	std::cout << "\nРезультат из файла: " << ans << "\n";
}
