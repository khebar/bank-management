#include "customer.h"
using namespace std;
Customer::Customer(const string& first, const string& last, 
    const string& national, int userAge,
    const string& user, const string& pass)
    : User(first, last, national, userAge, user, pass) {
}

Customer::~Customer() {
    for (int i = 0; i < accounts.getSize(); i++) {
        delete accounts.get(i);
    }
}

string Customer::getUserType() const {
    return "Customer";
}
bool Customer::addAccount(Account* account) {
    if (getAccountCount() >= MAX_ACCOUNTS) {
        return false; // حداکثر تعداد حساب
    }
    
    accounts.add(account);
    return true;
}

bool Customer::removeAccount(const string& accountNumber) {
    for (int i = 0; i < accounts.getSize(); i++) {
        if (accounts.get(i)->getAccountNumber() == accountNumber) {
            delete accounts.get(i);
            accounts.remove(i);
            return true;
        }
    }
    return false;
}

Account* Customer::findAccountByCardNumber(const string& cardNumber) {
    for (int i = 0; i < accounts.getSize(); i++) {
        if (accounts.get(i)->getCardNumber() == cardNumber) {
            return accounts.get(i);
        }
    }
    return nullptr;
}

Account* Customer::findAccountByAccountNumber(const string& accountNumber) {
    for (int i = 0; i < accounts.getSize(); i++) {
        if (accounts.get(i)->getAccountNumber() == accountNumber) {
            return accounts.get(i);
        }
    }
    return nullptr;
}

int Customer::getAccountCount() const {
    return accounts.getSize();
}