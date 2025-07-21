#include "admin.h"

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