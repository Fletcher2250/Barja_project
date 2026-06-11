#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <string>
#include <vector>

struct Command {
	char type;
	int compartment;
	int fuel_type;
};

std::string RunBargeSimulation(int n, int k, int p,
	const std::vector<Command>& commands);
int ReadSafeInt(int min_val, int max_val);
void HandleManualInput();
void HandleFileInput();

#endif