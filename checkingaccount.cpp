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

double CheckingAccount::getOverdraftLimit() const {
    return overdraftLimit;
}

void CheckingAccount::setOverdraftLimit(double limit) {
    if (limit >= 0) {
        overdraftLimit = limit;
    }
}

double CheckingAccount::getOverdraftInterest() const {
    return overdraftInterest;
}

bool CheckingAccount::withdraw(double amount) {
    if (amount <= 0) { 
        return false;
    }
    
    if (amount <= balance) {
        balance -= amount;
        return true;
    } else if (amount <= balance + overdraftLimit) {
        // استفاده از اضافه برداشت
        balance -= amount;
        return true;
    }
    
    return false;
}