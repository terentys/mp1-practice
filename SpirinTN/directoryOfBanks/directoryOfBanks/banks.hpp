#ifndef BANKS_H
#define BANKS_H

#include "bank.hpp"

class Banks {
private:
	Bank *banks;
	int countBanks;

	int _getCountBanksFromStream(std::istream& stream) const;
	void _copyFrom(const Banks& b);
public:
	Banks() noexcept : banks(nullptr), countBanks(0) {};
	Banks(const int countBanks);
	Banks(const char* nameFile);
    Banks(const Banks& b);
	~Banks() noexcept;

	void allocateBanks(const int count);

	void streamToBanks(std::istream& stream);
	void stringToBanks(const std::string& string);

    const Bank* getBanks() const noexcept;
    int getCountBanks() const noexcept;

	int findBank(const std::string& name) const;
	void removeBank();
	void removeBank(const int index);
	void removeBank(const std::string& name);
	void addBank(const Bank& b);
	void addBank(const Bank& b, const int index);

	Bank* searchMaxPercent(const std::string& depositType) const;
	Banks searchBanksWithDeposit(const std::string& depositType) const;
	Banks searchBanksWithOwnership(const std::string& ownership) const;

	Banks& operator=(const Banks& b);
	Bank& operator[](const int index);
	Banks operator|(const Banks& b);
	Banks operator&(const Banks& b);
	Banks operator-(const Banks& b);
	friend std::istream& operator>> (std::istream& is, Banks& b);
    friend std::ostream& operator<< (std::ostream& os, const Banks& bs);
};

#endif