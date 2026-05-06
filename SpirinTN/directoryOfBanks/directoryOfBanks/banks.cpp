#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

#include "banks.hpp"


Deposit::Deposit(const std::string& type, const float percent) {
    this->type = type;
    this->percent = percent;
}

Deposit& Deposit::operator= (const Deposit& d) {
	this->type = d.type;
	this->percent = d.percent;
	return (*this);
}

std::ostream& operator<< (std::ostream& os, const Deposit& d) {
	os << d.type << ": " << std::fixed << std::setprecision(2) << d.percent << "%";
	return os;
}

void Bank::_allocateDeposits(const std::string& strDeposits) {
	int count = 0;
	for (char c : strDeposits) {
		if (c == ':') {
			count++;
		}
	}
	this->depositsCount = count;
	this->deposits = new Deposit[count];
}

Bank::~Bank() {
    delete[] (this->deposits);
}

void Bank::stringToDeposit(std::string& string) {
	this->_allocateDeposits(string);
    int idx = 0;
    while (true) {
        size_t lenDepositSubStr = string.find(';');
        std::string depositSumStr = lenDepositSubStr != std::string::npos ? string.substr(0, lenDepositSubStr) : string;

		size_t idxColons = depositSumStr.find(':');
        if (idxColons == std::string::npos || !isFloat(depositSumStr.substr(idxColons + 1))) {
            throw std::runtime_error("Информация о депозитах некорректна! (1)");
        }

        const std::string type = depositSumStr.substr(0, idxColons);
        const float percent = std::stof(depositSumStr.substr(idxColons + 1));
        (this->deposits)[idx++] = Deposit(type, percent);

        if (lenDepositSubStr != std::string::npos) {
            string = string.substr(lenDepositSubStr + 1);
        }
        else {
            break;
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Bank& b) {
	os << '[' << b.name << ']' << "\nФорма собственности: " << b.ownership << "\nВклады:\n";
	for (int i = 0; i < b.depositsCount; i++) {
		os << "   " << b.deposits[i] << "\n";
	}
	return os;
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

int Banks::_getCountBanks(std::ifstream& file) const {
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
		splitIndex = line.find(';');
		if (splitIndex == std::string::npos) {
			throw std::runtime_error("Информация о депозитах некорректна! (2)");
		}
		this->banks[indexBank].name = line.substr(0, splitIndex);
		line = line.substr(splitIndex + 1);

		splitIndex = line.find(';');
		if (splitIndex == std::string::npos) {
			throw std::runtime_error("Информация о депозитах некорректна! (3)");
		}
		this->banks[indexBank].ownership = line.substr(0, splitIndex);
		line = line.substr(splitIndex + 1);

		this->banks[indexBank].stringToDeposit(line);
		indexBank++;
	}
}

Banks::Banks(const char* nameFile) {
	std::ifstream file(nameFile);
	if (!file) {
		throw std::runtime_error("Не удалось открыть файл!");
	}

	this->countBanks = this->_getCountBanks(file);
	file.clear();
	file.seekg(0, std::ios::beg);

	this->banks = new Bank[this->countBanks];
	this->_stringToBank(file);
}

Banks::~Banks() {
	delete[] (this->banks);
}

std::ostream& operator<< (std::ostream& os, const Banks& bs) {
	os << "Список банков в файле:\n\n";
	for (int i = 0; i < bs.countBanks; i++) {
		os << (i + 1) << ". " << bs.banks[i] << "\n";
	}
	return os;
}

Bank* Banks::searchMaxPercent(const std::string& depositType) const {
	const std::string lowerDepositType = toLower(depositType);
	float maxPercent = 0;
	Bank* resultBank = nullptr;

	for (int i = 0; i < this->countBanks; i++) {
		for (int j = 0; j < this->banks[i].depositsCount; j++) {
			std::string lowerType = toLower(this->banks[i].deposits[j].type);
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