#include "qarzaccount.h"
#include <cmath>
using namespace std;
QarzAccount::QarzAccount(const string& cardNum, const string& accNum, 
    const string& ibanNum, double initialBalance,
    double loan, double rate, int termMonths)
    : Account(cardNum, accNum, ibanNum, initialBalance),
      loanAmount(loan), interestRate(rate), loanTermMonths(termMonths),
      remainingInstallments(termMonths) {
    
    // محاسبه قسط ماهانه با فرمول وام
    double monthlyRate = rate / 100 / 12;
    monthlyPayment = loanAmount * monthlyRate * pow(1 + monthlyRate, termMonths) / 
                   (pow(1 + monthlyRate, termMonths) - 1);
}

string QarzAccount::getAccountType() const {
    return "Qarz Account";
}

double QarzAccount::getInterestRate() const {
    return interestRate;
}