
#include "User.h"

User::User(const std::string& first, const std::string& last, 
           const std::string& national, int userAge,
           const std::string& user, const std::string& pass)
    : firstName(first), lastName(last), nationalCode(national),
      age(userAge), username(user), password(pass) {
}
string User::getFirstName() const {
    return firstName;
}
string User::getLastName() const {
    return lastName;
}
string User::getNationalCode() const {
    return nationalCode;
}
int User::getAge() const {
    return age;
}
string User::getUsername() const {
    return username;
}
bool User::verifyPassword(const string& pass) const {
    return password == pass;
}
bool User::changePassword(const string& oldPass, const string& newPass) {
    if (verifyPassword(oldPass)) {
        password = newPass;
        return true;
    }
    return false;
}
