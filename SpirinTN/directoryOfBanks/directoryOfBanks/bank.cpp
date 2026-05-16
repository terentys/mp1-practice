#include <iostream>
#include <string>

#include "bank.hpp"

int Bank::_findCountDeposits(const std::string& string) {
    int count = 0;
    for (char c : string) {
        if (c == ':') {
            count++;
        }
    }
    return count;
}

void Bank::_copyFrom(const Bank& b) {
    this->name = b.getName();
    this->ownership = b.getOwnership();
    delete[] this->deposits;
    this->deposits = nullptr;
    this->depositsCount = 0;
    this->allocateDeposits(b.getDepositsCount());
    for (int i = 0; i < this->depositsCount; i++) {
        this->deposits[i] = b.getDeposits()[i];
    }
}

const char* Bank::_ownershipTypeToStr(const OwnershipType type) const {
    switch (type) {
    case OOO:
        return "ООО";
        break;
    case AO:
        return "АО";
        break;
    case PAO:
        return "ПАО";
        break;
    }
}

Bank::Bank(const Bank& b) : deposits(nullptr), depositsCount(0) {
    this->_copyFrom(b);
}

Bank::~Bank() noexcept {
    delete[](this->deposits);
}

void Bank::setName(const std::string& name) {
    if (name.empty()) {
        throw std::runtime_error("Название банка не может быть пустым!");
    }
    this->name = name;
}

void Bank::setOwnership(const std::string& ownership) {
    OwnershipType type;
    if (ownership == "АО") type = AO;
    else if (ownership == "ПАО") type = PAO;
    else if (ownership == "ООО") type = OOO;
    else throw;
    this->ownership = type;
}

void Bank::allocateDeposits(const int count) {
    if (count < 0 && count) {
        throw std::runtime_error("Недопустимый размер массива депозитов");
    }

    Deposit* newDeposits = new Deposit[count];
    try {
        for (int i = 0; i < count && i < this->depositsCount; i++) {
            newDeposits[i] = this->deposits[i];
        }
    }
    catch (...) {
        delete[] newDeposits;
        throw std::runtime_error("Ошибка выделения памяти!");
    }

    delete[](this->deposits);
    this->deposits = newDeposits;
    this->depositsCount = count;
}

void Bank::stringToDeposits(std::string& string) {
    int maxCount = _findCountDeposits(string);

    if (maxCount == 0) {
        delete[] deposits;
        deposits = nullptr;
        depositsCount = 0;
        return;
    }

    Deposit* parsed = nullptr;
    int idx = 0;

    try {
        parsed = new Deposit[maxCount];

        while (true) {
            size_t lenDepositSubStr = string.find(';');
            std::string depositSumStr = lenDepositSubStr != std::string::npos
                ? string.substr(0, lenDepositSubStr)
                : string;

            Deposit temp;
            temp.stringToDeposit(depositSumStr);

            bool duplicate = false;
            for (int i = 0; i < idx; ++i) {
                if (toLower(parsed[i].getType()) == toLower(temp.getType())) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                parsed[idx++] = temp;
            }

            if (lenDepositSubStr != std::string::npos) {
                string = string.substr(lenDepositSubStr + 1);
            }
            else {
                break;
            }
        }
    }
    catch (const std::bad_alloc& ex) {
        delete[] parsed;
        throw std::runtime_error("Ошибка выделения памяти!");
    }
    catch (...) {
        delete[] parsed;
        throw std::runtime_error("Некорректна строка депозита!");
    }

    Deposit* newDeposits = nullptr;
    try {
        if (idx > 0) {
            newDeposits = new Deposit[idx];
            for (int i = 0; i < idx; ++i) {
                newDeposits[i] = parsed[i];
            }
        }
    }
    catch (...) {
        delete[] newDeposits;
        delete[] parsed;
        throw std::runtime_error("Ошибка выделения памяти!");
    }

    delete[] parsed;
    delete[] deposits;
    deposits = newDeposits;
    depositsCount = idx;
}

void Bank::stringToBank(std::string& string) {
    size_t splitIndex = string.find(';');
    if (splitIndex == std::string::npos) {
        throw std::runtime_error("Строка банка некорректна! (отсутствует форма собственности)");
    }
    try {
        this->setName(string.substr(0, splitIndex));
    }
    catch (...) {
        throw std::runtime_error("Строка банка некорректна! (название банка отсутствует)");
    }
    string = string.substr(splitIndex + 1);

    splitIndex = string.find(';');
    if (splitIndex == std::string::npos) {
        throw std::runtime_error("Строка банка некорректна! (отсутствует перечисление депозитов)");
    }
    try {
        this->setOwnership( string.substr(0, splitIndex) );
    }
    catch (...) {
        throw std::runtime_error("Строка банка некорректна! (неправильная форма собственности)");
    }
    string = string.substr(splitIndex + 1);

    try {
        this->stringToDeposits(string);
    }
    catch (...) {
        throw std::runtime_error("Строка банка некорректна! (некорректна строка депозитов)");
    }
}

const std::string& Bank::getName() const noexcept {
    return this->name;
}

OwnershipType Bank::getOwnership() const noexcept {
    return this->ownership;
}

const Deposit* Bank::getDeposits() const noexcept {
    return this->deposits;
}

int Bank::getDepositsCount() const noexcept {
    return this->depositsCount;
}

int Bank::findDeposit(const std::string& type) const {
    const std::string lowerType = toLower(type);
    for (int i = 0; i < this->depositsCount; i++) {
        if (toLower(this->deposits[i].getType()) == lowerType) {
            return i;
        }
    }
    return -1;
}

const Bank& Bank::operator=(const Bank& b) {
    if (this == &b) return *this;
    this->_copyFrom(b);
    return *this;
}

std::ostream& operator<< (std::ostream& os, const Bank& b) {
    os << '[' << b.name << ']' << "\nФорма собственности: " << b._ownershipTypeToStr(b.ownership) << "\nВклады:\n";
    for (int i = 0; i < b.depositsCount; i++) {
        os << "   " << b.deposits[i] << "\n";
    }
    return os;
}

std::string toLower(const std::string& str) {
    std::string lowerStr;
    lowerStr.reserve(str.length());
    for (char c : str) {
        lowerStr.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return lowerStr;
}