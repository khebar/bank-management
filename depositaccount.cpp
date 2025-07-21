#include "depositaccount.h"
using namespace std;
DepositAccount::DepositAccount(const string& cardNum, const string& accNum, const string& ibanNum, double initialBalance, double rate, int termMonths)
    : Account(cardNum, accNum, ibanNum, initialBalance), 
      interestRate(rate), depositTermMonths(termMonths) {}
string DepositAccount::getAccountType() const {
    return "Deposit Account";
}
double DepositAccount::getInterestRate() const {
    return interestRate;
}
double DepositAccount::calculateInterest(int months) const {
    return balance * (interestRate / 100) * (months / 12.0);
}

int DepositAccount::getRemainingTerm() const {
    return depositTermMonths;
}

void DepositAccount::extendTerm(int additionalMonths) {
    if (additionalMonths > 0) {
        depositTermMonths += additionalMonths;
    }
}