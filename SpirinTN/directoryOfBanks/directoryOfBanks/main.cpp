#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

#include "auxiliary.hpp"
#include "banks.hpp"


int main(int argc, char** argv) {
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    if (argc < 2) {
		printFrame();
		std::cout << "Недостаточно аргументов!\n" << std::endl;
        return 1;
    }

	try {
		Banks banks(argv[1]);
		programCycle(banks);
	}
	catch (const char* ex) {
		printFrame();
		std::cout << ex;
		return 1;
	}

    return 0;
}