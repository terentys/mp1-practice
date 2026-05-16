#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <string>
#include <iostream>

class Deposit {
private:
    std::string type;
    float percent;
public:
    Deposit() noexcept : type(""), percent(0.0f) {};
    Deposit(const std::string& type, const float percent);

    void setType(const std::string& type);
    void setPercent(const float percent);

    void stringToDeposit(const std::string& str);

    const std::string& getType() const noexcept;
    float getPercent() const noexcept;

    const Deposit& operator= (const Deposit& d);
    friend std::ostream& operator<< (std::ostream& os, const Deposit& d);
    
};

#endif