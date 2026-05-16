#ifndef BANK_H
#define BANK_H

#include "deposit.hpp"

enum OwnershipType {
    NOT_OWNED = -1,
	OOO,
	AO,
	PAO,
};

class Bank {
private:
    std::string name;
    OwnershipType ownership;
    Deposit* deposits;
    int depositsCount;

    int _findCountDeposits(const std::string& string);
    void _copyFrom(const Bank& b);
    const char* _ownershipTypeToStr(const OwnershipType type) const;
public:
    Bank() noexcept : name(""), ownership(NOT_OWNED), deposits(nullptr), depositsCount(0) {};
    Bank(const Bank& b);
    ~Bank() noexcept;

    void setName(const std::string& name);
    void setOwnership(const std::string& ownership);
    void allocateDeposits(const int count);

    void stringToDeposits(std::string& string);
    void stringToBank(std::string& string);

    const std::string& getName() const noexcept;
    OwnershipType getOwnership() const noexcept;
    const Deposit* getDeposits() const noexcept;
    int getDepositsCount() const noexcept;

    int findDeposit(const std::string& type) const;

    const Bank& operator=(const Bank& b);
    friend std::ostream& operator<< (std::ostream& os, const Bank& b);
};

std::string toLower(const std::string& str);

#endif