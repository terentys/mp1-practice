#include <iostream>
#include <string>
#include <locale>


#include "auxiliary.hpp"
#include "banks.hpp"


int main(int argc, char** argv) {
	std::locale::global(std::locale("Russian"));
	system("chcp 1251");

    if (argc < 2) {
		printFrame();
		std::cout << "Недостаточно аргументов!\n" << std::endl;
        return 1;
    }

	try {
		Banks banks(argv[1]);
		programCycle(banks);
	}
	catch (const std::exception& ex) {
		printFrame();
		std::cerr << ex.what();
		return 1;
	}

    return 0;
}