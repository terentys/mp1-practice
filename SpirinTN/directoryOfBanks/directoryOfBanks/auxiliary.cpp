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
"3. Демо функционала классов Deposit, Bank, Banks\n"
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
            if (op >= 0 && op <= 3) {
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
    } while (!valid);

    return op;
}

void programCycle(Banks& banks) {
	while (true) {
		printFrame();
		std::cout << OPERATIONS;
		int op = inputOperation();
		std::cin.ignore();
		if (op == 1) {
			printListBanksInterface(banks);
		}
		else if (op == 2) {
			searchMaxInterface(banks);
		}
		else if (op == 3) {
			system("pause");
		}
		else {
			break;
		}
	}
}

void printListBanksInterface(Banks& banks) {
	printFrame();
	std::cout << banks;
	system("pause");
}

void searchMaxInterface(Banks& banks) {
	printFrame();
	const std::string depositType = inputDepositType();
	Bank* bank = banks.searchMaxPercent(depositType);
	if (bank == nullptr) {
		std::cout << "Банка с таким видом вклада не найдено!" << std::endl;
	}
	else {
		std::cout << "\nИнформация о банке с самым выгодным процентом на вид вклада \"" << depositType << "\":\n\n" << *bank << std::endl;
	}
	system("pause");
}

std::string inputDepositType() {
	bool valid = false;
	std::string type;

	do {
		std::cout << "Введите вид вклада: ";
		std::getline(std::cin, type);
		if (type.empty()) {
			std::cout << "Вы ничего не ввели!" << std::endl;
		}
		else {
			valid = true;
		}
	} while (!valid);
	return type;
}