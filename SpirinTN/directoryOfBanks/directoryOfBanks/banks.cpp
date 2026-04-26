#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

#include "banks.hpp"


Deposit::Deposit(const std::string& type, const float percent) {
    this->type = type;
    this->percent = percent;
}

std::string Deposit::getFullInfoDeposit() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << percent;
    return type + ": " + oss.str() + "%";
}

std::string Deposit::toLowerType() const {
    std::string lowerType;
    lowerType.reserve(type.length());
    for (char c : type) {
        lowerType.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return lowerType;
}

Bank::Bank(const std::string& name, const std::string& ownership, const int depositsCount) {
    this->name = name;
    this->ownership = ownership;
    this->depositsCount = depositsCount;
    this->deposits = new Deposit[depositsCount];
}

Bank::~Bank() {
    delete[] this->deposits;
}

void Bank::stringToDeposit(std::string& string) {
    int idx = 0;
    while (true) {
        int lenDepositSubStr = string.find(";");
        std::string depositSumStr = lenDepositSubStr != std::string::npos ? string.substr(0, lenDepositSubStr) : string;

        int idxColons = depositSumStr.find(":");
        if (idxColons == std::string::npos || !isFloat(depositSumStr.substr(idxColons + 1))) {
            throw "Информация о депозитах некорректна!";
        }

        std::string type = depositSumStr.substr(0, idxColons);
        float percent = std::stof(depositSumStr.substr(idxColons + 1));
        deposits[idx++] = Deposit(type, percent);

        if (lenDepositSubStr != std::string::npos) {
            string = string.substr(lenDepositSubStr + 1);
        }
        else {
            break;
        }
    }
}

std::string Bank::getFullInfoBank() const {

}

bool isFloat(const std::string& str) {
    std::istringstream iss(str);
    float value;
    char leftover;

    if (iss >> value) {
        return !(iss >> leftover);
    }
    return false;
}