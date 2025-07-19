#include "account.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <random>

Account::Account(const std::string& cardNum, const std::string& accNum, 
                 const std::string& ibanNum, double initialBalance)
    : cardNumber(cardNum), accountNumber(accNum), iban(ibanNum),
      balance(initialBalance), hasDynamicPin(false) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> cvvDist(100, 9999);
    cvv2 = std::to_string(cvvDist(gen));
    
    std::time_t now = std::time(nullptr);
    std::tm* futureTime = std::localtime(&now);
    futureTime->tm_year += 4;
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << (futureTime->tm_mon + 1) << "/";
    ss << (futureTime->tm_year % 100);
    expirationDate = ss.str();
    
    firstPin = "1234";
    secondPin = "12345";
}
string Account::getCardNumber() const {
    return cardNumber;
}
string Account::getAccountNumber() const {
    return accountNumber;
}
string Account::getIban() const {
    return iban;
}
string Account::getCvv2() const {
    return cvv2;
}
string Account::getExpirationDate() const {
    return expirationDate;
}
double Account::getBalance() const {
    return balance;
}
void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}
bool Account::changeFirstPin(const string& oldPin, const string& newPin){
    if (firstPin == oldPin && newPin.length() == 4) {
        firstPin = newPin;
        return true;
    }
    return false;
}

bool Account::changeSecondPin(const string& oldPin, const string& newPin){
    if (secondPin == oldPin && newPin.length() == 5) {
        secondPin = newPin;
        return true;
    }
    return false;
}
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}