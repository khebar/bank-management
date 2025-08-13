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

const LinkedList<Account*>& Customer::getAccounts() const {
    return accounts;
}

bool Customer::cardTransfer(const string& sourceCardNumber, 
    const string& destinationCardNumber,
    double amount, const string& pin) {
    // بررسی مقدار انتقال
    if (amount <= 0) {
        return false;
    }
    
    // پیدا کردن حساب مبدا
    Account* sourceAccount = findAccountByCardNumber(sourceCardNumber);
    if (sourceAccount == nullptr) {
        return false; // حساب مبدا یافت نشد
    }
    
    // بررسی سقف و محدودیت‌های تراکنش
    if (!sourceAccount->checkTransferLimits(amount)) {
        return false;
    }
    
    // بررسی رمز
    bool validPin = false;
    if (amount <= 100000) { // تا 100 هزار تومان با رمز دوم ثابت
        // اینجا باید رمز دوم ثابت  بررسی بشه
        validPin = true;
    } else {
        // بیشتر از 100 هزار تومان نیاز به رمز دوم پویا
        validPin = sourceAccount->verifyDynamicPin(pin);
    }
    
    if (!validPin) {
        return false;
    }
    
    // محاسبه کارمزد
    double fee = sourceAccount->calculateTransferFee(amount);
    
    // بررسی موجودی (مبلغ + کارمزد)
    if (sourceAccount->getBalance() < amount + fee) {
        return false;
    }
    
    // انجام تراکنش
    sourceAccount->withdraw(amount + fee);
    
    return true;
}