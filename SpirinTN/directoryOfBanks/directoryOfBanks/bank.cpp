#include <iostream>
#include <string>

#include "bank.hpp"

const std::string Bank::LIST_OWNERSHIP = ";АО;ПАО;ООО;";
const int Bank::MAX_COUNT = 10000;

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

Bank::Bank(const std::string& name, const std::string& ownership, const int depositsCount) : deposits(nullptr), depositsCount(0) {
    this->setName(name);
    this->setOwnership(ownership);
    this->allocateDeposits(depositsCount);
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
    else if (name.length() > 256) {
        throw std::runtime_error("Название банка слишком длинное!");
    }
    this->name = name;
}

void Bank::setOwnership(const std::string& ownership) {
    if (LIST_OWNERSHIP.find(";" + ownership + ";") == std::string::npos) {
        throw std::runtime_error("Такого общества не существует!");
    }
    this->ownership = ownership;
}

void Bank::allocateDeposits(const int count) {
    if (count < 0 && count > this->MAX_COUNT) {
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
    this->setName( string.substr(0, splitIndex) );
    string = string.substr(splitIndex + 1);

    splitIndex = string.find(';');
    if (splitIndex == std::string::npos) {
        throw std::runtime_error("Строка банка некорректна! (отсутствует перечисление депозитов)");
    }
    this->setOwnership( string.substr(0, splitIndex) );
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

const std::string& Bank::getOwnership() const noexcept {
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

void Bank::removeDeposit() {
    if (this->depositsCount == 0) {
        throw std::runtime_error("Депозитов у банка нет!");
    }

    Deposit* copyDeposits = new Deposit[this->depositsCount - 1];
    try {
        for (int i = 0; i < this->depositsCount - 1; i++) {
            copyDeposits[i] = this->deposits[i];
        }
    }
    catch (...) {
        delete[] copyDeposits;
        throw std::runtime_error("Ошибка при удалении депозита!");
    }

    delete[] this->deposits;
    this->deposits = copyDeposits;
    --(this->depositsCount);
}

void Bank::removeDeposit(const int index) {
    if (index < 0 || index > this->depositsCount - 1) {
        throw std::runtime_error("Депозита с таким индексом нет!");
    }

    Deposit* copyDeposits = new Deposit[this->depositsCount - 1];
    try {
        int k;
        for (k = 0; k < index && k < this->depositsCount - 1; k++) {
            copyDeposits[k] = this->deposits[k];
        }
        for (; k < this->depositsCount - 1; k++) {
            copyDeposits[k] = this->deposits[k + 1];
        }
    }
    catch (...) {
        delete[] copyDeposits;
        throw std::runtime_error("Ошибка при удалении депозита!");
    }

    delete[] this->deposits;
    this->deposits = copyDeposits;
    --(this->depositsCount);
}

void Bank::removeDeposit(const std::string& type) {
    int indexDeposit = this->findDeposit(type);
    if (indexDeposit == -1) {
        throw std::runtime_error("Депозита с таким названием нет!");
    }
    this->removeDeposit(indexDeposit);
}

void Bank::addDeposit(const Deposit& d) {
    if (this->depositsCount + 1 > MAX_COUNT) {
        throw std::runtime_error("У банка максимум депозитов!");
    }

    if (findDeposit(d.getType()) != -1) {
        throw std::runtime_error("Депозит с названием \"" + d.getType() + "\" уже существует!");
    }

    Deposit* copyDeposits = new Deposit[this->depositsCount + 1];
    try {
        for (int i = 0; i < this->depositsCount; i++) {
            copyDeposits[i] = this->deposits[i];
        }
        copyDeposits[this->depositsCount] = d;
    }
    catch (...) {
        delete[] copyDeposits;
        throw std::runtime_error("Ошибка при добавлении депозита!");
    }

    delete[] this->deposits;
    this->deposits = copyDeposits;
    ++(this->depositsCount);
}

void Bank::addDeposit(const Deposit& d, const int index) {
    if (index < 0 || index > this->depositsCount || index >= MAX_COUNT) {
        throw std::runtime_error("Недопустимая позиция для добавления депозита!");
    }

    if (findDeposit(d.getType()) != -1) {
        throw std::runtime_error("Депозит с названием \"" + d.getType() + "\" уже существует!");
    }

    Deposit* copyDeposits = new Deposit[this->depositsCount + 1];
    try {
        int k;
        for (k = 0; k < index && k < this->depositsCount; k++) {
            copyDeposits[k] = this->deposits[k];
        }
        copyDeposits[k++] = d;
        for (; k < this->depositsCount; k++) {
            copyDeposits[k] = this->deposits[k - 1];
        }
    }
    catch (...) {
        delete[] copyDeposits;
        throw std::runtime_error("Ошибка при добавлении депозита!");
    }

    delete[] this->deposits;
    this->deposits = copyDeposits;
    ++(this->depositsCount);
}

Deposit& Bank::getDepositForEdit(const int index) {
    if (index < 0 || index >= this->depositsCount) {
        throw std::runtime_error("Депозита с таким индексом нет!");
    }
    return this->deposits[index];
}

Deposit& Bank::getDepositForEdit(const std::string& type) {
    int index = this->findDeposit(type);
    if (index == -1) {
        throw std::runtime_error("Депозита с таким названием нет!");
    }
    return this->deposits[index];
}

const Deposit* Bank::getMaxPercentDeposit() const {
    Deposit* ptrDeposit = nullptr;
    float maxPercent = 0.0f;
    for (int i = 0; i < this->depositsCount; i++) {
        if (this->deposits[i].getPercent() > maxPercent) {
            maxPercent = this->deposits[i].getPercent();
            ptrDeposit = &(this->deposits[i]);
        }
    }
    return ptrDeposit;
}

Bank& Bank::operator=(const Bank& b) {
    this->_copyFrom(b);
    return *this;
}

std::istream& Bank::inputDeposits(std::istream& is) {
    std::string inputLine;
    if (std::getline(is, inputLine)) {
        this->stringToDeposits(inputLine);
    }
    return is;
}

std::istream& operator>> (std::istream& is, Bank& d) {
    std::string inputLine;
    if (std::getline(is, inputLine)) {
        d.stringToBank(inputLine);
    }
    return is;
}

std::ostream& operator<< (std::ostream& os, const Bank& b) {
    os << '[' << b.name << ']' << "\nФорма собственности: " << b.ownership << "\nВклады:\n";
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