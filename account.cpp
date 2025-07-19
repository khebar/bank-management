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