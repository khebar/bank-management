#ifndef QARZACCOUNT_H
#define QARZACCOUNT_H

#include "account.h"
#include <string>

class QarzAccount : public Account {
private:
    double loanAmount;// مبلغ وام
    double interestRate;// نرخ بهره وام
    int loanTermMonths;// مدت وام به ماه
    int remainingInstallments; // اقساط باقیمانده
    double monthlyPayment;// مبلغ قسط ماهانه

public:
    QarzAccount(const std::string& cardNum, const std::string& accNum, 
               const std::string& ibanNum, double initialBalance,
               double loan, double rate, int termMonths);
    
    std::string getAccountType() const override;
    double getInterestRate() const override;
    double getLoanAmount() const;
    int getRemainingInstallments() const;
    double getMonthlyPayment() const;
    bool payInstallment();
    double getTotalPayable() const;
};

#endif // QARZACCOUNT_H
