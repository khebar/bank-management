#include "customer.h"
using namespace std;
Customer::Customer(const string& first, const string& last, 
    const string& national, int userAge,
    const string& user, const string& pass)
    : User(first, last, national, userAge, user, pass) {
}

Customer::~Customer() {
    for (int i = 0; i < accounts.getSize(); i++) {
        delete accounts.get(i);
    }
}

std::string Customer::getUserType() const {
    return "Customer";
}