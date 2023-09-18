#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <iostream>
#include "Printable.h"

class Account: public Printable{
    static constexpr double def_balance = 0.0;
    static constexpr const char *def_name = "Unnamed Account";
protected:
    std::string name;
    double balance; // make it protected, so that it is visible in inheriting classes
public:
    Account(std::string name = def_name, double balance = def_balance);
    virtual bool deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
    double get_balance() const;
    virtual ~Account() = default;
    virtual void print(std::ostream &os) const override;
};
#endif