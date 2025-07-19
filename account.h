#include <iostream>
#include <string>
using namespace std;

class Account{
protected:
    std::string cardNumber;
    std::string accountNumber;
    std::string iban;
    std::string cvv2;
    std::string expirationDate;
    double balance;
    std::string firstPin;
    std::string secondPin;
    std::string dynamicPin;
    bool hasDynamicPin;

public:
    Account(const std::string& cardNum, const std::string& accNum, 
            const std::string& ibanNum, double initialBalance);
    virtual ~Account() = default;
    
    virtual std::string getAccountType() const = 0;
    virtual double getInterestRate() const = 0;
};