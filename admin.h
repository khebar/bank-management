#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "customer.h"
#include "linkedlist.h"
using namespace std;
class Admin : public User {
private:
    static LinkedList<Admin*> allAdmins;
    static LinkedList<Customer*> allCustomers;
    static LinkedList<Account*> allAccounts;

public:
    Admin(const string& first, const string& last, 
         const string& national, int userAge,
         const string& user, const string& pass);
    ~Admin() override;
    string getUserType() const override;
};

#endif