#pragma once

#include <string>
#include <iostream>

namespace mmfbank {
    class Account {
    private:
        std::string login;
        unsigned int accountNumber;
        double balance;
        unsigned long long passwordHash;

        static unsigned long long hashPassword(unsigned int password);
        static std::string generateRandomLogin();
        static double generateRandomBalance();

    public:
        Account();
        Account(const std::string& login, unsigned int accountNumber, double balance, unsigned int password);

        static Account generateRandomAccount(int accountIndex);

        const std::string& getLogin() const;
        unsigned int getAccountNumber() const;
        double getBalance() const;

        void addFunds(double amount);
        void withdrawFunds(double amount);
        bool validatePassword(unsigned int password) const;

        friend std::ostream& operator<<(std::ostream& os, const Account& account);
    };
}