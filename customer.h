#include "user.h"
#include "account.h"
#include "linkedlist.h"
using namespace std;
class Customer : public User {
private:
    LinkedList<Account*> accounts;
    static const int MAX_ACCOUNTS = 5;// حداکثر تعداد حساب‌ها برای هر مشتری

public:
    Customer(const string& first, const string& last, 
    const string& national, int userAge,
    const string& user, const string& pass);
    ~Customer() override;
    string getUserType() const override;
    bool addAccount(Account* account);
    bool removeAccount(const string& accountNumber);
    Account* findAccountByCardNumber(const string& cardNumber);
    Account* findAccountByAccountNumber(const string& accountNumber);
    int getAccountCount() const;
};