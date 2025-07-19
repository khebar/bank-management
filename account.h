#include <iostream>
#include <string>
using namespace std;

class Account{
protected:
    string cardNumber;
    string accountNumber;
    string iban;
    string cvv2;
    string expirationDate;
    double balance;
    string firstPin;
    string secondPin;
    string dynamicPin;
    bool hasDynamicPin;

public:
    Account(const std::string& cardNum, const std::string& accNum, 
            const std::string& ibanNum, double initialBalance);
    virtual ~Account() = default;
    
    virtual std::string getAccountType() const = 0;
    virtual double getInterestRate() const = 0;
};