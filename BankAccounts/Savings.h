#ifndef _SACCOUNT_H_
#define _SACCOUNT_H_
#include <iostream>
#include "Account.h"
class SavingsAccount: public Account{
    static constexpr double def_balance = 0.0;
    static constexpr const char *def_name = "Unnamed";
    static constexpr double def_int_rate = 0.0;
protected:
    double int_rate;
public:
    SavingsAccount(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate);
    virtual bool deposit(double amount) override;
    virtual bool withdraw(double amount) override{return Account::withdraw(amount);}
    virtual ~SavingsAccount() = default;
    void print(std::ostream &os) const override;
};
#endif