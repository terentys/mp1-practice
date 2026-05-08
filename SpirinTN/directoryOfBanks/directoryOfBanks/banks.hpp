#ifndef BANKS_H
#define BANKS_H


#include <string>
#include <fstream>

struct Deposit {
    std::string type;
    float percent;

    Deposit() noexcept : type(""), percent(0.0f) {};
    Deposit(const std::string& type, const float percent);

    Deposit& operator= (const Deposit& d);
    friend std::ostream& operator<< (std::ostream& os, const Deposit& d);
};

struct Bank {
    std::string name;
    std::string ownership;
    Deposit* deposits;
    int depositsCount;

    void _allocateDeposits(const std::string& strDeposits);

    Bank() noexcept : name(""), ownership(""), deposits(nullptr), depositsCount(0) {};
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();

    void stringToDeposit(std::string& string);

    friend std::ostream& operator<< (std::ostream& os, const Bank& b);
};

struct Banks {
	Bank *banks;
	int countBanks;

	int _getCountBanks(std::ifstream& file) const;
	void _stringToBank(std::ifstream& file);

	Banks() noexcept : banks(nullptr), countBanks(0) {};
	Banks(const char* nameFile);
    Banks(const Banks&) = delete;
    Banks& operator=(const Banks&) = delete;
	~Banks();

	Bank* searchMaxPercent(const std::string& depositType) const;

    friend std::ostream& operator<< (std::ostream& os, const Banks& bs);
};

bool isFloat(const std::string& str);
std::string toLower(const std::string& str);

#endif