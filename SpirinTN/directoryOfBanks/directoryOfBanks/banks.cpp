#include <iostream>
#include <string>
#include <fstream>

#include "banks.hpp"

int Banks::_getCountBanksFromStream(std::istream& stream) const {
	int count = 0;
	std::string line;
	while (std::getline(stream, line)) {
		count++;
	}
	return count;
}

void Banks::_copyFrom(const Banks& b) {
	delete[] this->banks;
	this->banks = nullptr;
	this->countBanks = 0;
	allocateBanks(b.getCountBanks());
	for (int i = 0; i < this->countBanks; i++) {
		this->banks[i] = b.getBanks()[i];
	}
}

Banks::Banks(const int countBanks) : banks(nullptr), countBanks(0) {
	this->allocateBanks(countBanks);
}

Banks::Banks(const Banks& b) : banks(nullptr), countBanks(0) {
	this->_copyFrom(b);
}

Banks::Banks(const char* nameFile) {
	std::ifstream file(nameFile);
	if (!file) {
		throw std::runtime_error("Не удалось открыть файл!");
	}

	this->allocateBanks( this->_getCountBanksFromStream(file) );

	file.clear();
	file.seekg(0, std::ios::beg);
	this->streamToBanks(file);
}

Banks::~Banks() noexcept {
	delete[] (this->banks);
}

void Banks::allocateBanks(const int count) {
	if (count < 0) {
		throw std::runtime_error("Недопустимый размер массива банков");
	}

	Bank* newBanks = new Bank[count];
	try {
		for (int i = 0; i < count && i < this->countBanks; i++) {
			newBanks[i] = this->banks[i];
		}
	}
	catch (...) {
		delete[] newBanks;
		throw std::runtime_error("Ошибка выделения памяти!");
	}

	delete[](this->banks);
	this->banks = newBanks;
	this->countBanks = count;
}

void Banks::streamToBanks(std::istream& stream) {
	int indexBank = 0;
	std::string line;
	while (indexBank < this->countBanks && std::getline(stream, line)) {
		this->banks[indexBank++].stringToBank(line);
	}
}

void Banks::stringToBanks(const std::string& string) {
	int indexBank = 0;
	std::string fullString = string;
	while (indexBank < this->countBanks && !fullString.empty()) {
		size_t indexTransfer = fullString.find('\n');
		std::string bankStr = indexTransfer != std::string::npos ? fullString.substr(0, indexTransfer) : fullString;
		this->banks[indexBank++].stringToBank(bankStr);

		if (indexTransfer == std::string::npos) break;
		fullString = fullString.substr(indexTransfer + 1);
	}
}

const Bank* Banks::getBanks() const noexcept {
	return this->banks;
}

int Banks::getCountBanks() const noexcept {
	return this->countBanks;
}

int Banks::findBank(const std::string& name) const {
    const std::string lowerName = toLower(name);
    for (int i = 0; i < this->countBanks; i++) {
        if (toLower(this->banks[i].getName()) == lowerName) {
            return i;
        }
    }
    return -1;
}

void Banks::removeBank() {
    if (this->countBanks == 0) {
        throw std::runtime_error("В множестве банков нет!");
    }

    Bank* copyBanks = new Bank[this->countBanks - 1];
    try {
        for (int i = 0; i < this->countBanks - 1; i++) {
            copyBanks[i] = this->banks[i];
        }
    }
    catch (...) {
        delete[] copyBanks;
        throw std::runtime_error("Ошибка при удалении банка!");
    }

    delete[] this->banks;
    this->banks = copyBanks;
    --(this->countBanks);
}

void Banks::removeBank(const int index) {
    if (index < 0 || index > this->countBanks - 1) {
        throw std::runtime_error("Банка с таким индексом нет!");
    }

    Bank* copyBanks = new Bank[this->countBanks - 1];
    try {
        int k;
        for (k = 0; k < index && k < this->countBanks - 1; k++) {
            copyBanks[k] = this->banks[k];
        }
        for (; k < this->countBanks - 1; k++) {
            copyBanks[k] = this->banks[k + 1];
        }
    }
    catch (...) {
        delete[] copyBanks;
        throw std::runtime_error("Ошибка при удалении банка!");
    }

    delete[] this->banks;
    this->banks = copyBanks;
    --(this->countBanks);
}

void Banks::removeBank(const std::string& name) {
    int indexDeposit = this->findBank(name);
    if (indexDeposit == -1) {
        throw std::runtime_error("Банка с таким названием нет!");
    }
    this->removeBank(indexDeposit);
}

void Banks::addBank(const Bank& b) {
    if (findBank(b.getName()) != -1) {
        throw std::runtime_error("Банк с названием \"" + b.getName() + "\" уже существует!");
    }

    Bank* copyBanks = new Bank[this->countBanks + 1];
    try {
        for (int i = 0; i < this->countBanks; i++) {
            copyBanks[i] = this->banks[i];
        }
        copyBanks[this->countBanks] = b;
    }
    catch (...) {
        delete[] copyBanks;
        throw std::runtime_error("Ошибка при добавлении банка!");
    }

    delete[] this->banks;
    this->banks = copyBanks;
    ++(this->countBanks);
}

void Banks::addBank(const Bank& b, const int index) {
    if (index < 0 || index > this->countBanks) {
        throw std::runtime_error("Недопустимая позиция для добавления банка!");
    }

    if (findBank(b.getName()) != -1) {
        throw std::runtime_error("Банк с названием \"" + b.getName() + "\" уже существует!");
    }

    Bank* copyBanks = new Bank[this->countBanks + 1];
    try {
        int k;
        for (k = 0; k < index && k < this->countBanks; k++) {
            copyBanks[k] = this->banks[k];
        }
        copyBanks[k++] = b;
        for (; k < this->countBanks; k++) {
            copyBanks[k] = this->banks[k - 1];
        }
    }
    catch (...) {
        delete[] copyBanks;
        throw std::runtime_error("Ошибка при добавлении депозита!");
    }

    delete[] this->banks;
    this->banks = copyBanks;
    ++(this->countBanks);
}

Bank* Banks::searchMaxPercent(const std::string& depositType) const {
	float maxPercent = 0;
	Bank* resultBank = nullptr;

	for (int i = 0; i < this->countBanks; i++) {
		const int idxDeposit = this->banks[i].findDeposit(depositType);
		if (idxDeposit != -1 && this->banks[i].getDeposits()[idxDeposit].getPercent() > maxPercent) {
			maxPercent = this->banks[i].getDeposits()[idxDeposit].getPercent();
			resultBank = &(this->banks[i]);
		}
	}

	return resultBank;
}

Banks& Banks::operator=(const Banks& b) {
	this->_copyFrom(b);
	return *this;
}

Bank& Banks::operator[](const int index) {
	if (index < 0 || index >= this->countBanks) {
		throw std::runtime_error("Выход за пределы массива!");
	}
	return this->banks[index];
}

std::istream& operator>> (std::istream& is, Banks& b) {
	is >> b.countBanks;
	b.allocateBanks(b.countBanks);
	for (int i = 0; i < b.countBanks; i++) {
		is >> b.banks[i];
	}
	return is;
}

std::ostream& operator<< (std::ostream& os, const Banks& bs) {
	os << "Список банков в файле:\n\n";
	for (int i = 0; i < bs.countBanks; i++) {
		os << (i + 1) << ". " << bs.banks[i] << "\n";
	}
	return os;
}