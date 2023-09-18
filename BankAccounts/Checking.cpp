#include "Checking.h"

void CheckingAccount::print(std::ostream &os) const{
    Account::print(os);
    os<<" fee: "<<fee;
}

CheckingAccount::CheckingAccount(std::string name, double balance, double fee)
        :Account{name, balance}, fee{fee}{}

bool CheckingAccount::withdraw(double amount){
    amount += fee;
    return Account::withdraw(amount);
}