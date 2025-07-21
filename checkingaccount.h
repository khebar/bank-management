#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "account.h"
#include <string>
using namespace std;
class CurrentAccount : public Account {
private:
    double overdraftLimit;  // سقف اضافه برداشت
    double overdraftInterest; // نرخ بهره اضافه برداشت

public:
    CurrentAccount(const string& cardNum, const string& accNum, 
                   const string& ibanNum, double initialBalance,
                   double overLimit = 0.0, double overInterest = 0.0);
    
    string getAccountType() const override;
    double getInterestRate() const override;
};

#endif // CURRENTACCOUNT_H