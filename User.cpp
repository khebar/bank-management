
#include "User.h"

User::User(const std::string& first, const std::string& last, 
           const std::string& national, int userAge,
           const std::string& user, const std::string& pass)
    : firstName(first), lastName(last), nationalCode(national),
      age(userAge), username(user), password(pass) {
}