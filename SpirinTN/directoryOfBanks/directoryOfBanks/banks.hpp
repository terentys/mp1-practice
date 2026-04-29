#ifndef AUXILIARY_H
#define AUXILIARY_H


#include <string>
#include <fstream>

struct Deposit {
    std::string type;
    float percent;

    Deposit() {};
    Deposit(const std::string& type, const float percent);

    std::string getFullInfoDeposit() const;
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

struct Banks {
	Bank *banks;
	int countBanks;

	int _getCountBanks(std::ifstream& file);
	void _stringToBank(std::ifstream& file);

	Banks() {};
	Banks(const char* nameFile);
	~Banks();

	std::string getFullLustBanks() const;
	Bank& searchMaxPercent(const std::string& depositType) const;
};

std::string toLower(const std::string& str);

#endif