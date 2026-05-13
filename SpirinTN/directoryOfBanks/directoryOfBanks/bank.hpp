#ifndef BANK_H
#define BANK_H

#include "deposit.hpp"

enum OwnershipType {
	OOO,
	AO,
	PAO,
};

class Bank {
private:
    std::string name;
    std::string ownership; // OwnershipType
    Deposit* deposits;
    int depositsCount;

    int _findCountDeposits(const std::string& string);
    void _copyFrom(const Bank& b);

    static const std::string LIST_OWNERSHIP;
    static const int MAX_COUNT;
public:
    Bank() noexcept : name(""), ownership(""), deposits(nullptr), depositsCount(0) {};
    Bank(const std::string& name, const std::string& ownership, const int depositsCount);
    Bank(const Bank& b);
    ~Bank() noexcept;

    void setName(const std::string& name);
    void setOwnership(const std::string& ownership);
    void allocateDeposits(const int count);

    void stringToDeposits(std::string& string);
    void stringToBank(std::string& string);

    const std::string& getName() const noexcept;
    const std::string& getOwnership() const noexcept;
    const Deposit* getDeposits() const noexcept;
    int getDepositsCount() const noexcept;

    int findDeposit(const std::string& type) const;
    void removeDeposit();
    void removeDeposit(const int index);
    void removeDeposit(const std::string& type);
    void addDeposit(const Deposit& d);
    void addDeposit(const Deposit& d, const int index);

    Deposit& getDepositForEdit(const int index);
    Deposit& getDepositForEdit(const std::string& type);

    const Deposit* getMaxPercentDeposit() const;

    Bank& operator=(const Bank& b);
    std::istream& inputDeposits(std::istream& is);
    friend std::istream& operator>> (std::istream& is, Bank& d);
    friend std::ostream& operator<< (std::ostream& os, const Bank& b);
};

std::string toLower(const std::string& str);

#endif