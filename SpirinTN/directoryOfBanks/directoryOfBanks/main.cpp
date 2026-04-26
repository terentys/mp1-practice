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
        return 1;
    }

    return 0;
}