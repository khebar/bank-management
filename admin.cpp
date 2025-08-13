#include "admin.h"
using namespace std;
LinkedList<Admin*> Admin::allAdmins;
LinkedList<Customer*> Admin::allCustomers;
LinkedList<Account*> Admin::allAccounts;

Admin::Admin(const string& first, const string& last, 
    const string& national, int userAge,
    const string& user, const string& pass)
    : User(first, last, national, userAge, user, pass) {
}

Admin::~Admin() {}

string Admin::getUserType() const {
    return "Admin";
}
bool Admin::addCustomer(Customer* customer) {
    if (findCustomerByUsername(customer->getUsername()) != nullptr ||
        findCustomerByNationalCode(customer->getNationalCode()) != nullptr) {
        return false; // کاربر تکراری با نام کاربری یا کد ملی
    }
    
    allCustomers.add(customer);
    return true;
}

bool Admin::removeCustomer(const string& username) {
    for (int i = 0; i < allCustomers.getSize(); i++) {
        if (allCustomers.get(i)->getUsername() == username) {
            // حذف حساب‌های کاربری مشتری قبل از حذف مشتری
            LinkedList<Account*> accounts = allCustomers.get(i)->getAccounts();
            for (int j = 0; j < accounts.getSize(); j++) {
                for (int k = 0; k < allAccounts.getSize(); k++) {
                    if (allAccounts.get(k) == accounts.get(j)) {
                        allAccounts.remove(k);
                        break;
                    }
                }
            }
            
            delete allCustomers.get(i);
            allCustomers.remove(i);
            return true;
        }
    }
    return false;
}

Customer* Admin::findCustomerByUsername(const string& username) {
    for (int i = 0; i < allCustomers.getSize(); i++) {
        if (allCustomers.get(i)->getUsername() == username) {
            return allCustomers.get(i);
        }
    }
    return nullptr;
}

Customer* Admin::findCustomerByNationalCode(const string& nationalCode) {
    for (int i = 0; i < allCustomers.getSize(); i++) {
        if (allCustomers.get(i)->getNationalCode() == nationalCode) {
            return allCustomers.get(i);
        }
    }
    return nullptr;
}
bool Admin::addAccount(Account* account, Customer* owner) {
    if (owner->getAccountCount() >= 5) {
        return false; // هر مشتری حداکثر 5 حساب می‌تواند داشته باشد
    }
    
    allAccounts.add(account);
    owner->addAccount(account);
    return true;
}

bool Admin::removeAccount(const string& accountNumber) {
    Account* account = findAccountByAccountNumber(accountNumber);
    if (account == nullptr) {
        return false;
    }
    
    // حذف از لیست کلی حساب‌ها
    for (int i = 0; i < allAccounts.getSize(); i++) {
        if (allAccounts.get(i) == account) {
            allAccounts.remove(i);
            break;
        }
    }
    
    // حذف از حساب‌های مشتری
    for (int i = 0; i < allCustomers.getSize(); i++) {
        Customer* customer = allCustomers.get(i);
        if (customer->findAccountByAccountNumber(accountNumber) != nullptr) {
            customer->removeAccount(accountNumber);
            return true;
        }
    }
    
    return false;
}

Account* Admin::findAccountByAccountNumber(const string& accountNumber) {
    for (int i = 0; i < allAccounts.getSize(); i++) {
        if (allAccounts.get(i)->getAccountNumber() == accountNumber) {
            return allAccounts.get(i);
        }
    }
    return nullptr;
}

Account* Admin::findAccountByCardNumber(const string& cardNumber) {
    for (int i = 0; i < allAccounts.getSize(); i++) {
        if (allAccounts.get(i)->getCardNumber() == cardNumber) {
            return allAccounts.get(i);
        }
    }
    return nullptr;
}

bool Admin::addAdmin(Admin* admin) {
    if (findAdminByUsername(admin->getUsername()) != nullptr) {
        return false; // ادمین با این نام کاربری قبلاً وجود دارد
    }
    
    allAdmins.add(admin);
    return true;
}

bool Admin::removeAdmin(const string& username) {
    for (int i = 0; i < allAdmins.getSize(); i++) {
        if (allAdmins.get(i)->getUsername() == username) {
            delete allAdmins.get(i);
            allAdmins.remove(i);
            return true;
        }
    }
    return false;
}

Admin* Admin::findAdminByUsername(const string& username) {
    for (int i = 0; i < allAdmins.getSize(); i++) {
        if (allAdmins.get(i)->getUsername() == username) {
            return allAdmins.get(i);
        }
    }
    return nullptr;
}

const LinkedList<Admin*>& Admin::getAllAdmins() {
    return allAdmins;
}

const LinkedList<Customer*>& Admin::getAllCustomers() {
    return allCustomers;
}

const LinkedList<Account*>& Admin::getAllAccounts() {
    return allAccounts;
}