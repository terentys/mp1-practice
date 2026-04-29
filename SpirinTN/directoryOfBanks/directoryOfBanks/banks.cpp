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
	std::string result = this->name + ":\nФорма собственности: " + this->ownership + "\nВклады:\n";
	for (int i = 0; i < this->depositsCount; i++) {
		result += "\t" + this->deposits[i].getFullInfoDeposit() + "\n";
	}
	return result;
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

int Banks::_getCountBanks(std::ifstream& file) {
	int count;
	std::string line;
	while (std::getline(file, line)) {
		count++;
	}
	return count;
}

void Banks::_stringToBank(std::ifstream& file) {
	int indexBank = 0;
	std::string line;
	while (indexBank < this->countBanks && std::getline(file, line)) {

	}
}

Banks::Banks(const char* nameFile) {
	throw std::runtime_error("no realization");
}

Banks::~Banks() {
	throw std::runtime_error("no realization");
}

std::string toLower(const std::string& str) {
	std::string lowerStr;
	lowerStr.reserve(str.length());
	for (char c : str) {
		lowerStr.push_back(std::tolower(static_cast<unsigned char>(c)));
	}
	return lowerStr;
}