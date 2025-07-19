#include <iostream>
#include <string>
using namespace std;
class User{
private:
    string name;
    string email;
    string password;
protected:
    string firstName;
    string lastName;
    string nationalCode;
    int age;
    string username;
    string password;
public:
    User(const string& firstName, const string& lastName, const string& nationalCode, int age, const string& username, const string& password);
    virtual ~User() = default;
    virtual string getUserType() const = 0;
    string getFirstName() const;
    string getLastName() const;
    string getNationalCode() const;
    int getAge() const;
    string getUsername() const;
    
};