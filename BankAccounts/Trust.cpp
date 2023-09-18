#include "Trust.h"

TrustAccount::TrustAccount(std::string name, double balance, double int_rate,
        double floorbonus, double bonus)
            :SavingsAccount{name, balance, int_rate}, floorbonus{floorbonus}, bonus{bonus}{}
    
bool TrustAccount::deposit(double amount){
    if (amount >= 5000.0)
        amount += 50;
    return SavingsAccount::deposit(amount);
}

bool TrustAccount::withdraw(double amount){
    if (balance*0.2<amount || withdrawals == 3)
        return false;
    withdrawals++;
    return SavingsAccount::withdraw(amount);
}

void TrustAccount::print(std::ostream &os) const{
    SavingsAccount::print(os);
    os<<" start of the bonus: "<<floorbonus<<" bonus: "<<bonus;
}