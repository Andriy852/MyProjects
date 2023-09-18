#include "Savings.h"
#include "UtilFunc.h"
#include "Trust.h"
using namespace std;
int main(){
    Account *Andrii_save = new SavingsAccount("Andrii", 1000, 0.09);
    Account *Andrii_check = new CheckingAccount("Andrii", 900, 30);
    Account *Andrii_trust = new TrustAccount("Andrii", 800, 0.1, 5000, 50);

    vector <Account *> Andrii{Andrii_check, Andrii_save, Andrii_trust};
    display(Andrii);
    

}