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
        size_t lenDepositSubStr = string.find(";");
        std::string depositSumStr = lenDepositSubStr != std::string::npos ? string.substr(0, lenDepositSubStr) : string;

		size_t idxColons = depositSumStr.find(":");
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
	int count = 0;
	std::string line;
	while (std::getline(file, line)) {
		count++;
	}
	return count;
}

void Banks::_stringToBank(std::ifstream& file) {
	int indexBank = 0;
	std::string line;
	size_t splitIndex;
	while (indexBank < this->countBanks && std::getline(file, line)) {
		splitIndex = line.find(";");
		if (splitIndex == std::string::npos) {
			throw "Информация о депозитах некорректна!";
		}
		this->banks[indexBank].name = line.substr(0, splitIndex);
		line = line.substr(splitIndex + 1);

		splitIndex = line.find(";");
		if (splitIndex == std::string::npos) {
			throw "Информация о депозитах некорректна!";
		}
		this->banks[indexBank].ownership = line.substr(0, splitIndex);
		line = line.substr(splitIndex + 1);

		this->banks[indexBank].stringToDeposit(line);
	}
}

Banks::Banks(const char* nameFile) {
	std::ifstream file(nameFile);
	if (!file) {
		throw "Не удалось открыть файл!";
	}

	this->countBanks = this->_getCountBanks(file);
	file.clear();
	file.seekg(0, std::ios::beg);

	this->banks = new Bank[this->countBanks];
	this->_stringToBank(file);
}

Banks::~Banks() {
	delete[] this->banks;
}

std::string Banks::getFullListBanks() const {
	std::string result = "Список банков в файле:\n\n";
	for (int i = 0; i < this->countBanks; i++) {
		result += this->banks[i].getFullInfoBank() + "\n";
	}
	return result;
}

Bank* Banks::searchMaxPercent(const std::string& depositType) const {
	std::string lowerDepositType = toLower(depositType);
	float maxPercent = 0;
	Bank* resultBank = nullptr;

	for (int i = 0; i < this->countBanks; i++) {
		for (int j = 0; j < this->banks[i].depositsCount; j++) {
			std::string lowerType = this->banks[i].deposits[j].type;
			if (lowerDepositType == lowerType) {
				if (this->banks[i].deposits[j].percent > maxPercent) {
					maxPercent = this->banks[i].deposits[j].percent;
					resultBank = &(this->banks[i]);
				}
			}
		}
	}

	return resultBank;
}

std::string toLower(const std::string& str) {
	std::string lowerStr;
	lowerStr.reserve(str.length());
	for (char c : str) {
		lowerStr.push_back(std::tolower(static_cast<unsigned char>(c)));
	}
	return lowerStr;
}