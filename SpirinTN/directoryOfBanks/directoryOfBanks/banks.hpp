#ifndef AUXILIARY_H
#define AUXILIARY_H


#include <string>

struct Deposit {
    std::string type;
    float percent;

    Deposit() {};
    Deposit(const std::string& type, const float percent);

    std::string getFullInfoDeposit() const;
    std::string toLowerType() const;
};

struct Bank {
    std::string name;
    std::string ownership;
    Deposit* deposits;
    int depositsCount;

    Bank() {};
    Bank(const std::string& name, const std::string& ownership, const int depositsCount);
    ~Bank();

    void stringToDeposit(std::string& string);
    std::string getFullInfoBank() const;
};

bool isFloat(const std::string& str);


#endif