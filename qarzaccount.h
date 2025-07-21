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
};
