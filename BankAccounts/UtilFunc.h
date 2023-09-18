#ifndef _UTIL_FUNC_H_
#define _UTIL_FUNC_H_
#include <vector>
#include "Savings.h"
#include "Checking.h"

void display(const std::vector <Account *> &Accounts);
void deposit(std::vector <Account *> &Accounts, double amount);
void withdraw(std::vector <Account *> &Accounts, double amount);

#endif