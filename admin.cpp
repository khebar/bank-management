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