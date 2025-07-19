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

    virtual string getAccountType() const = 0;
    virtual double getInterestRate() const = 0;
    string getCardNumber() const;
    string getAccountNumber() const;
    string getIban() const;
    string getCvv2() const;
    string getExpirationDate() const;
    double getBalance() const;
    bool withdraw(double amount);
    bool deposit(double amount);
    bool changeFirstPin(const string& oldPin, const string& newPin);
    bool changeSecondPin(const string& oldPin, const string& newPin);
    string generateDynamicPin();
    bool validateDynamicPin(const string& pin);
};