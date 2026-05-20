#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

#include "banks.hpp"


Deposit::Deposit(const std::string& type, const float percent) {
    this->type = type;
    this->percent = percent;
}

const Deposit& Deposit::operator= (const Deposit& d) {
	if (this == &d) return *this;
	this->type = d.type;
	this->percent = d.percent;
	return (*this);
}

std::ostream& operator<< (std::ostream& os, const Deposit& d) {
	os << d.type << ": " << std::fixed << std::setprecision(2) << d.percent << "%";
	return os;
}

void Bank::_copyFrom(const Bank& b) {
	this->name = b.name;
	this->ownership = b.ownership;

	Deposit* newDeposits = nullptr;
	try {
		if (b.depositsCount > 0) {
			newDeposits = new Deposit[b.depositsCount];
			for (int i = 0; i < b.depositsCount; i++) {
				newDeposits[i] = b.deposits[i];
			}
		}
	}
	catch (...) {
		if (newDeposits != nullptr) delete[] newDeposits;
		throw std::runtime_error("Ошибка при выделении памяти!");
	}

	delete[] this->deposits;
	this->deposits = newDeposits;
	this->depositsCount = b.depositsCount;
}

Bank::Bank(const Bank& b) : deposits(nullptr), depositsCount(0) {
	this->_copyFrom(b);
}

Bank::~Bank() {
    delete[] (this->deposits);
}

void Bank::stringToDeposit(const std::string& string) {
	int count = 0;
	for (char c : string) {
		if (c == ':') {
			count++;
		}
	}
	this->depositsCount = count;
	this->deposits = new Deposit[count];

	std::string editableString = string;
    int idx = 0;
    while (true) {
        size_t lenDepositSubStr = editableString.find(';');
        std::string depositSumStr = lenDepositSubStr != std::string::npos ? editableString.substr(0, lenDepositSubStr) : editableString;

		size_t idxColons = depositSumStr.find(':');
		try {
			const std::string type = depositSumStr.substr(0, idxColons);
			const float percent = std::stof(depositSumStr.substr(idxColons + 1));
			(this->deposits)[idx++] = Deposit(type, percent);
		}
		catch (...) {
			throw std::runtime_error("Информация о депозитах некорректна! (1)");
		}

        if (lenDepositSubStr != std::string::npos) {
			editableString = editableString.substr(lenDepositSubStr + 1);
        }
        else {
            break;
        }
    }
}

const Bank& Bank::operator=(const Bank& b) {
	if (this == &b) return *this;
	this->_copyFrom(b);
	return *this;
}

std::ostream& operator<< (std::ostream& os, const Bank& b) {
	os << '[' << b.name << ']' << "\nФорма собственности: " << b.ownership << "\nВклады:\n";
	for (int i = 0; i < b.depositsCount; i++) {
		os << "   " << b.deposits[i] << "\n";
	}
	return os;
}

int Banks::_getCountBanks(std::ifstream& file) const {
	int count = 0;
	std::string line;
	while (std::getline(file, line)) {
		count++;
	}

	file.clear();
	file.seekg(0, std::ios::beg);
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

void Banks::_copyFrom(const Banks& b) {
	Bank* newBanks = nullptr;
	try {
		if (b.countBanks > 0) {
			newBanks = new Bank[b.countBanks];
			for (int i = 0; i < b.countBanks; i++) {
				newBanks[i] = b.banks[i];
			}
		}
	}
	catch (...) {
		if (newBanks != nullptr) delete[] newBanks;
		throw std::runtime_error("Ошибка при выделении памяти!");
	}

	delete[] this->banks;
	this->banks = newBanks;
	this->countBanks = b.countBanks;
}

Banks::Banks(const std::string& nameFile) {
	std::ifstream file(nameFile);
	if (!file) {
		throw std::runtime_error("Не удалось открыть файл!");
	}

	this->countBanks = this->_getCountBanks(file);

	this->banks = new Bank[this->countBanks];
	this->_stringToBank(file);
}

Banks::Banks(const Banks& b) : banks(nullptr), countBanks(0) {
	this->_copyFrom(b);
}

Banks::~Banks() {
	delete[] (this->banks);
}

const Banks& Banks::operator=(const Banks& b) {
	if (this == &b) return *this;
	this->_copyFrom(b);
	return *this;
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