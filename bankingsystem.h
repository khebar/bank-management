#include "user.h"
#include "customer.h"
#include "admin.h"
using namespace std;
class BankingSystem {
private:
    User* currentUser;
    static BankingSystem* instance;
    
    BankingSystem();

public:
    ~BankingSystem();
    
    static BankingSystem* getInstance();
    
    // Login/logout
    bool login(const string& username, const string& password);
    void logout();
    User* getCurrentUser() const;
};