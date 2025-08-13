#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "account.h"
#include <string>
using namespace std;

class CheckingAccount : public Account {
private:
    double overdraftLimit;  // سقف اضافه برداشت
    double overdraftInterest; // نرخ بهره اضافه برداشت

public:
    CheckingAccount(const string& cardNum, const string& accNum, 
                   const string& ibanNum, double initialBalance,
                   double overLimit = 0.0, double overInterest = 0.0);
    double getOverdraftLimit() const;
    void setOverdraftLimit(double limit);
    double getOverdraftInterest() const;
    bool withdraw(double amount) override; // بازنویسی برای پشتیبانی از اضافه برداشت
    string getAccountType() const override;
    double getInterestRate() const override;
};

#endif // CHECKINGACCOUNT_H