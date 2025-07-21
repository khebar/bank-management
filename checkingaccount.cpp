#include "checkingaccount.h"
using namespace std;
CheckingAccount::CheckingAccount(const string& cardNum, const string& accNum, 
                               const string& ibanNum, double initialBalance,
                               double overLimit, double overInterest)
    : Account(cardNum, accNum, ibanNum, initialBalance),
      overdraftLimit(overLimit), overdraftInterest(overInterest) {
}

string CheckingAccount::getAccountType() const {
    return "Checking Account";
}

double CheckingAccount::getInterestRate() const {
    return 0.0; // حساب جاری اغلب اوقات سود ندارد
}