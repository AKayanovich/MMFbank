#include "Account.h"
#include <iomanip>
#include <ctime>

namespace mmfbank {
    Account::Account() :
        login(""),
        accountNumber(0),
        balance(0.0),
        passwordHash(0)
    {
       
    }

    Account::Account(const std::string& login, unsigned int accountNumber, double balance, unsigned int password) :
        login(login),
        accountNumber(accountNumber),
        balance(balance),
        passwordHash(hashPassword(password))
    {
    }

    Account Account::generateRandomAccount(int accountIndex) {


        unsigned int accountNumber = accountIndex + 9000;
        unsigned int password = accountIndex + 9900;
        std::string randomLogin = generateRandomLogin();
        double randomBalance = generateRandomBalance();

        return Account(randomLogin, accountNumber, randomBalance, password);
    }

    std::string Account::generateRandomLogin() {
        const std::string adjectives[] = { "Amazing", "Brilliant", "Creative", "Dynamic" };
        const std::string colors[] = { "Red", "Blue", "Green", "Yellow" };

        return adjectives[rand() % 4] + colors[rand() % 4] + std::to_string(rand() % 999);
    }

    double Account::generateRandomBalance() {
        return (rand() % 10000) + 1.0;
    }

    unsigned long long Account::hashPassword(unsigned int password) {
        return (password * 31) * (password * 31) + password * 17;
    }

    const std::string& Account::getLogin() const {
        return login;
    }

    unsigned int Account::getAccountNumber() const {
        return accountNumber;
    }

    double Account::getBalance() const {
        return balance;
    }

    void Account::addFunds(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    void Account::withdrawFunds(double amount) {
        if (amount <= 0) {
            throw "Invalid amount";
        }
        if (balance >= amount) {
            balance -= amount;
        }
        else {
            throw "Insufficient funds";
        }
    }

    bool Account::validatePassword(unsigned int password) const {
        return passwordHash == hashPassword(password);
    }

    std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << std::fixed << std::setprecision(2);
        os << "Login: " << account.login << "\n"
            << "Account Number: " << account.accountNumber << "\n"
            << "Balance: $" << account.balance << "\n";
        return os;
    }
}