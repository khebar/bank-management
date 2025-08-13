#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "account.h"
#include <string>
using namespace std;

class CurrentAccount : public Account {
private:
    double overdraftLimit;  // سقف اضافه برداشت
    double interestRate;    // نرخ بهره

public:
    CurrentAccount(const string& cardNum, const string& accNum, 
                   const string& ibanNum, double initialBalance,
                   double overLimit = 0.0, double interest = 0.0);
    
    double getOverdraftLimit() const;
    void setOverdraftLimit(double limit);
    bool withdraw(double amount) override; // بازنویسی برای پشتیبانی از اضافه برداشت
    string getAccountType() const override;
    double getInterestRate() const override;
};

#endif // CURRENTACCOUNT_H
