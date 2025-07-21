#include "account.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <random>
using namespace std;
Account::Account(const string& cardNum, const string& accNum, 
                 const string& ibanNum, double initialBalance)
    : cardNumber(cardNum), accountNumber(accNum), iban(ibanNum),
      balance(initialBalance), hasDynamicPin(false), dailyTransferTotal(0.0) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> cvvDist(100, 9999);
    cvv2 = to_string(cvvDist(gen));
    
    time_t now = time(nullptr);
    tm* futureTime = localtime(&now);
    futureTime->tm_year += 4;
    
    stringstream ss;
    ss << setfill('0') << setw(2) << (futureTime->tm_mon + 1) << "/";
    ss << (futureTime->tm_year % 100);
    expirationDate = ss.str();
    
    firstPin = "1234";
    secondPin = "12345";
    std::tm* currentTime = std::localtime(&now);
    ss.str("");
    ss << (currentTime->tm_year + 1900) << "-";
    ss << setfill('0') << setw(2) << (currentTime->tm_mon + 1) << "-";
    ss << setfill('0') << setw(2) << currentTime->tm_mday;
    lastTransferDate = ss.str();
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
string Account::generateDynamicPin(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100000, 999999);
    dynamicPin = to_string(dist(gen));
    hasDynamicPin = true;
    return dynamicPin;
}
bool Account::verifyDynamicPin(const string& pin) {
    if (hasDynamicPin && pin == dynamicPin)
    {
        hasDynamicPin = false;
        return true;
    }
    return false;
}

bool Account::checkTransferLimits(double amount) {
    // بررسی تاریخ فعلی
    std::time_t now = std::time(nullptr);
    std::tm* currentTime = std::localtime(&now);
    
    std::stringstream ss;
    ss << (currentTime->tm_year + 1900) << "-";
    ss << std::setfill('0') << std::setw(2) << (currentTime->tm_mon + 1) << "-";
    ss << std::setfill('0') << std::setw(2) << currentTime->tm_mday;
    std::string currentDate = ss.str();
    
    // اگر روز عوض شده، سقف روزانه ریست شود
    if (currentDate != lastTransferDate) {
        dailyTransferTotal = 0;
        lastTransferDate = currentDate;
    }
    
    // بررسی سقف تراکنش و سقف روزانه
    if (amount > 3000000) { // سقف تراکنش: 3 میلیون تومان
        return false;
    }
    
    if (dailyTransferTotal + amount > 10000000) { // سقف روزانه: 10 میلیون تومان
        return false;
    }
    
    return true;
}

double Account::calculateTransferFee(double amount) const {
    // کارمزد: 0.01% از مبلغ تراکنش
    return amount * 0.0001;
}

void Account::resetDailyLimit() {
    dailyTransferTotal = 0;
}