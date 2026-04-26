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