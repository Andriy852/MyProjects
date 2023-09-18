#ifndef _TRUST_H_
#define _TRUST_H_
#include "Savings.h"

class TrustAccount: public SavingsAccount{
    static constexpr const char *def_name = "Unnamed Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;
    static constexpr double def_floorbonus = 5000.0;
    static constexpr double def_bonus = 50.0;
protected:
    int withdrawals = 0;
    double floorbonus;
    double bonus;
public:
    TrustAccount(std::string name = def_name, double balance = def_balance,
        double int_rate = def_int_rate, double floorbonus = def_floorbonus, double bonus = def_bonus);
    virtual bool deposit(double amount) override;
    virtual bool withdraw(double amount) override;
    virtual ~TrustAccount() = default;
    virtual void print(std::ostream &os) const override;
};


#endif