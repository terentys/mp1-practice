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
	Banks(const char* nameFile);
    Banks(const Banks& b);
	~Banks() noexcept;

	void allocateBanks(const int count);

	void streamToBanks(std::istream& stream);

    const Bank* getBanks() const noexcept;
    int getCountBanks() const noexcept;

	Bank* searchMaxPercent(const std::string& depositType) const;

	const Banks& operator=(const Banks& b);
    friend std::ostream& operator<< (std::ostream& os, const Banks& bs);
};

#endif