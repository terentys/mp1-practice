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
	if (this->banks != nullptr) delete[] this->banks;
	this->banks = nullptr;
	this->countBanks = 0;
	allocateBanks(b.getCountBanks());
	for (int i = 0; i < this->countBanks; i++) {
		this->banks[i] = b.getBanks()[i];
	}
}

Banks::Banks(const Banks& b) : banks(nullptr), countBanks(0) {
	this->_copyFrom(b);
}

Banks::Banks(const std::string& nameFile) {
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
	if (this->banks != nullptr) delete[] (this->banks);
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
		if (newBanks != nullptr) delete[] newBanks;
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

const Bank* Banks::getBanks() const noexcept {
	return this->banks;
}

int Banks::getCountBanks() const noexcept {
	return this->countBanks;
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