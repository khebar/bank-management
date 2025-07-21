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
    
    
    bool login(const string& username, const string& password);
    void logout();
    User* getCurrentUser() const;
    void initializeSystem(); // پیاده سازی ابتدایی و اجرای سیستم با مقادیر اولیه
};