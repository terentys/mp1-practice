#include <iostream>
#include <cstdlib>
#include <limits>

#include "auxiliary.hpp"


const char* MAIN_FRAME = 
"|-----------------------------|\n"
"|      Справочник банков      |\n"
"|-----------------------------|\n\n";
const char* OPERATIONS =
"1. Показать список банков\n"
"2. Найти банк с максимальным процентом для вклада\n"
"0. Выход\n\n";

void printFrame() {
    system("cls");
    std::cout << MAIN_FRAME;
}

int inputOperation() {
    int op;
    bool valid = false;

    do {
        std::cout << "Введите операцию: ";
        if (std::cin >> op) {
            if (op >= 0 && op <= 2) {
                valid = true;
            }
            else {
                std::cout << "Некорректная операция! Введите число от 0 до 2!" << std::endl;
            }
        }
        else {
            std::cout << "Ошибка! Нужно ввести целое число от 0 до 2!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
    } while (valid);

    return op;
}

void programCycle(Banks& banks) {
	while (true) {
		printFrame();
		std::cout << OPERATIONS;
		int op = inputOperation();
		if (op == 1) {
			printListBanksInterface(banks);
		}
		else if (op == 2) {
			searchMaxInterface(banks);
		}
		else {
			break;
		}
	}
}

void printListBanksInterface(Banks& banks) {
	printFrame();
	std::cout << banks.getFullListBanks();
	system("pause");
}

void searchMaxInterface(Banks& banks) {
	printFrame();
	std::string depositType = inputDepositType();
	Bank* bank = banks.searchMaxPercent(depositType);
	if (bank == nullptr) {
		std::cout << "Банка с таким видом вклада не найдено!" << std::endl;
	}
	else {
		std::cout << "Информация о банке с самым выгодным процентом на вид вклада \"" << depositType << "\":\n\n" << bank->getFullInfoBank() << std::endl;
	}
	system("pause");
}

std::string inputDepositType() {
	std::string type;
	std::cin.ignore();
	std::getline(std::cin, type);
	return type;
}