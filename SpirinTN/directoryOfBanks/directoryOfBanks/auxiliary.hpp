#ifndef AUXILIARY_H
#define AUXILIARY_H


#include "banks.hpp"

void printFrame();
int inputOperation();
void programCycle(Banks& banks);
void printListBanksInterface(Banks& banks);
void searchMaxInterface(Banks& banks);
std::string inputDepositType();

#endif