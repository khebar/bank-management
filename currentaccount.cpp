#include "currentaccount.h"
#include <iostream>
using namespace std;

CurrentAccount::CurrentAccount(const string& cardNum, const string& accNum, 
                               const string& ibanNum, double initialBalance,
                               double overLimit, double interest)
    : Account(cardNum, accNum, ibanNum, initialBalance), 
      overdraftLimit(overLimit), interestRate(interest) {
}

double CurrentAccount::getOverdraftLimit() const {
    return overdraftLimit;
}

void CurrentAccount::setOverdraftLimit(double limit) {
    overdraftLimit = limit;
}

bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "مبلغ برداشت باید مثبت باشد." << endl;
        return false;
    }
    
    // بررسی موجودی + سقف اضافه برداشت
    if (amount > (balance + overdraftLimit)) {
        cout << "موجودی کافی نیست. موجودی فعلی: " << balance 
             << " سقف اضافه برداشت: " << overdraftLimit << endl;
        return false;
    }
    
    balance -= amount;
    cout << "مبلغ " << amount << " با موفقیت برداشت شد. موجودی جدید: " << balance << endl;
    return true;
}

string CurrentAccount::getAccountType() const {
    return "Current Account";
}

double CurrentAccount::getInterestRate() const {
    return interestRate;
}
