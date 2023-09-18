#ifndef _CHECKING_H_
#define _CHECKING_H_
#include "Account.h"

class CheckingAccount: public Account{
    static constexpr double def_fee = 1.5;
    static constexpr const char *def_name = "Unnamed Checking Account";
    static constexpr const double def_balance = 0.0;
protected:
    double fee;
public:
    CheckingAccount(std::string name = def_name, double balance = def_balance,
         double fee = def_fee);
    virtual bool withdraw(double amount) override;
    virtual bool deposit(double amount) override{return Account::deposit(amount);}
    virtual ~CheckingAccount() = default;
    virtual void print(std::ostream &os) const override;
};

#endif