#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "deposit.hpp"

Deposit::Deposit(const std::string& type, const float percent) {
	this->setType(type);
	this->setPercent(percent);
}

void Deposit::setType(const std::string& type) {
	if (type.empty()) {
		throw std::runtime_error("Название вида вклада не может быть пустым!");
	}
	this->type = type;
}

void Deposit::setPercent(const float percent) {
	if (percent < 0.0f) {
		throw std::runtime_error("Процент должен быть неотрицательным!");
	}
	else if (percent > 100.0f) {
		throw std::runtime_error("Процент не может быть больше 100!");
	}
	this->percent = percent;
}

void Deposit::stringToDeposit(const std::string& str) {
	size_t splitIndex = str.find(':');
	if (splitIndex == std::string::npos) {
		throw std::runtime_error("Строка депозита некорректна!");
	}
	this->setType(str.substr(0, splitIndex));
	try {
		this->setPercent(std::stof(str.substr(splitIndex + 1)));
	}
	catch (const std::invalid_argument& ex) {
		throw std::runtime_error("Строка депозита некорректна!");
	}
}

const std::string& Deposit::getType() const noexcept {
	return this->type;
}

float Deposit::getPercent() const noexcept {
	return this->percent;
}

const Deposit& Deposit::operator= (const Deposit& d) {
	this->type = d.getType();
	this->percent = d.getPercent();
	return (*this);
}

std::ostream& operator<< (std::ostream& os, const Deposit& d) {
	os << d.type << ": " << std::fixed << std::setprecision(2) << d.percent << "%";
	return os;
}