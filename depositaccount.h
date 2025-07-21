#include "account.h"
using namespace std;

class DepositAccount : public Account {
private:
    double interestRate;// نرخ سود
    int depositTermMonths; // مدت زمان سپرده گذاری به ماه
public:
    DepositAccount(const string& cardNum, const string& accNum, const string& ibanNum, double initialBalance, double rate, int termMonths);
    string getAccountType() const override;
    double getInterestRate() const override;
};