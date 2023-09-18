#include "UtilFunc.h"

void display(const std::vector <Account *> &Accounts){
    for (auto const account: Accounts){
        std::cout<<*account<<std::endl;
    }
}

void deposit(std::vector <Account *> &Accounts, double amount){
    for (auto account:Accounts){
        if (!account->deposit(amount))
            std::cout<<"Failed to deposit "<<amount<<" to "<<*account<<std::endl;
    }
}

void withdraw(std::vector <Account *> &Accounts, double amount){
    for (auto account:Accounts){
        if (!account->withdraw(amount))
            std::cout<<"Failed to withdraw "<<amount<<" from "<<*account<<std::endl;
    }
}
