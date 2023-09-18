#include "Savings.h"

SavingsAccount::SavingsAccount(std::string name, double balance, double int_rate):
    Account{name, balance}, int_rate{int_rate}{};

bool SavingsAccount::deposit(double amount){
    amount += amount*int_rate;
    return Account::deposit(amount);
}

void SavingsAccount::print(std::ostream &os) const{
    Account::print(os);
    os<<" interest rate: "<<int_rate;
}