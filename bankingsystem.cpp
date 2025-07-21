#include "bankingsystem.h"
using namespace std;

// Initialize static instance
BankingSystem* BankingSystem::instance = nullptr;

BankingSystem::BankingSystem() : currentUser(nullptr) {
}

BankingSystem::~BankingSystem() {
    // Clean up is handled by Admin class
}

BankingSystem* BankingSystem::getInstance() {
    if (instance == nullptr) {
        instance = new BankingSystem();
    }
    return instance;
}

bool BankingSystem::login(const string& username, const string& password) {
    // Check admins
    Admin* admin = Admin::findAdminByUsername(username);
    if (admin != nullptr && admin->verifyPassword(password)) {
        currentUser = admin;
        return true;
    }
    
    // Check customers
    Customer* customer = Admin::findCustomerByUsername(username);
    if (customer != nullptr && customer->verifyPassword(password)) {
        currentUser = customer;
        return true;
    }
    
    return false;
}

void BankingSystem::logout() {
    currentUser = nullptr;
}

User* BankingSystem::getCurrentUser() const {
    return currentUser;
}