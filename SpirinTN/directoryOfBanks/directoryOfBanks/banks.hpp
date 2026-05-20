#ifndef BANKS_H
#define BANKS_H


#include <string>
#include <fstream>

struct Deposit {
    std::string type;
    float percent;

    Deposit() noexcept : type(""), percent(0.0f) {};
    Deposit(const std::string& type, const float percent);

    const Deposit& operator= (const Deposit& d);
    friend std::ostream& operator<< (std::ostream& os, const Deposit& d);
};

struct Bank {
    std::string name;
    std::string ownership;
    Deposit* deposits;
    int depositsCount;

	void _copyFrom(const Bank& b);

    Bank() noexcept : name(""), ownership(""), deposits(nullptr), depositsCount(0) {};
    Bank(const Bank& b);
    ~Bank();

    void stringToDeposit(const std::string& string);

	const Bank& operator=(const Bank& b);
    friend std::ostream& operator<< (std::ostream& os, const Bank& b);
};

struct Banks {
	Bank *banks;
	int countBanks;

	int _getCountBanks(std::ifstream& file) const;
	void _stringToBank(std::ifstream& file);
	
	void _copyFrom(const Banks& b);

	Banks() noexcept : banks(nullptr), countBanks(0) {};
	Banks(const std::string& nameFile);
    Banks(const Banks& b);
	~Banks();

	Bank* searchMaxPercent(const std::string& depositType) const;

	const Banks& operator=(const Banks& b);
    friend std::ostream& operator<< (std::ostream& os, const Banks& bs);
};

std::string toLower(const std::string& str);

#endif