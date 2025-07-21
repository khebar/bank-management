#include "bankingsystem.h"
#include "depositaccount.h"
#include "checkingaccount.h"
#include "qarzaccount.h"
#include <random>
using namespace std;

// Initialize static instance
BankingSystem* BankingSystem::instance = nullptr;

BankingSystem::BankingSystem() : currentUser(nullptr) {
}

BankingSystem::~BankingSystem() {
    // Clean up is handled by Admin class
}

BankingSystem* BankingSystem::getInstance() {
    if (instance == nullptr) {
        instance = new BankingSystem();
    }
    return instance;
}

bool BankingSystem::login(const string& username, const string& password) {
    // Check admins
    Admin* admin = Admin::findAdminByUsername(username);
    if (admin != nullptr && admin->verifyPassword(password)) {
        currentUser = admin;
        return true;
    }
    
    // Check customers
    Customer* customer = Admin::findCustomerByUsername(username);
    if (customer != nullptr && customer->verifyPassword(password)) {
        currentUser = customer;
        return true;
    }
    
    return false;
}

void BankingSystem::logout() {
    currentUser = nullptr;
}

User* BankingSystem::getCurrentUser() const {
    return currentUser;
}

void BankingSystem::initializeSystem() {
    // تعریف ادمین پیش‌فرض و مشتریان اولیه
    // و حساب‌های اولیه برای تست
    Admin* admin = new Admin("Admin", "User", "0000000000", 30, "admin", "admin123");
    Admin::addAdmin(admin);
    
    Customer* customer = new Customer("John", "Doe", "1111111111", 25, "john", "john123");
    Admin::addCustomer(customer);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1000000000, 9999999999);
    
    string cardNum1 = to_string(dist(gen));
    string accNum1 = to_string(dist(gen));
    string iban1 = "IR" + to_string(dist(gen)) + to_string(dist(gen));
    
    DepositAccount* depositAcc = new DepositAccount(cardNum1, accNum1, iban1, 1000000, 15.0, 12);
    Admin::addAccount(depositAcc, customer);
    
    string cardNum2 = to_string(dist(gen));
    string accNum2 = to_string(dist(gen));
    string iban2 = "IR" + to_string(dist(gen)) + to_string(dist(gen()));

    CheckingAccount* checkingAcc = new CheckingAccount(cardNum2, accNum2, iban2, 500000, 200000, 18.0);
    Admin::addAccount(checkingAcc, customer);
    
    string cardNum3 = to_string(dist(gen));
    string accNum3 = to_string(dist(gen));
    string iban3 = "IR" + to_string(dist(gen)) + to_string(dist(gen));
    
    QarzAccount* qarzAcc = new QarzAccount(cardNum3, accNum3, iban3, 200000, 5000000, 4.0, 36);
    Admin::addAccount(qarzAcc, customer);
}
// متد های عملیات بانکی
bool BankingSystem::transferFunds(const string& sourceCard, const string& destCard, 
    double amount, const string& pin) {
    Customer* customer = dynamic_cast<Customer*>(currentUser);
    if (customer == nullptr) {
        return false;
    }
    
    return customer->cardTransfer(sourceCard, destCard, amount, pin);
}

bool BankingSystem::changePin(const string& cardNumber, const string& oldPin, 
    const string& newPin, bool isSecondPin) {
    Customer* customer = dynamic_cast<Customer*>(currentUser);
    if (customer == nullptr) {
        return false;
    }
    
    Account* account = customer->findAccountByCardNumber(cardNumber);
    if (account == nullptr) {
        return false;
    }
    
    if (isSecondPin) {
        return account->changeSecondPin(oldPin, newPin);
    } else {
        return account->changeFirstPin(oldPin, newPin);
    }
}

string BankingSystem::generateDynamicPin(const string& cardNumber) {
    Customer* customer = dynamic_cast<Customer*>(currentUser);
    if (customer == nullptr) {
        return "";
    }
    
    Account* account = customer->findAccountByCardNumber(cardNumber);
    if (account == nullptr) {
        return "";
    }
    
    return account->generateDynamicPin();
}