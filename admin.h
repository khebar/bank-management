
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
    static bool addCustomer(Customer* customer);
    static bool removeCustomer(const string& username);
    static Customer* findCustomerByUsername(const string& username);
    static Customer* findCustomerByNationalCode(const string& nationalCode);
    static bool addAccount(Account* account, Customer* owner);
    static bool removeAccount(const string& accountNumber);
    static Account* findAccountByAccountNumber(const string& accountNumber);
    static Account* findAccountByCardNumber(const string& cardNumber);
};
