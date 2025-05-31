#pragma once

#include "Account.h"

namespace mmfbank {
    class AccountDB {
    private:
        Account* accounts;
        int accountCount;
        int currentUserIndex;

    public:
        AccountDB(int amount = 10);
        ~AccountDB();

        void addAccount(const std::string& login, double balance = 1000.0);
        void addRandomAccount();
        Account* searchByLogin(const std::string& login);
        Account* searchByNumber(unsigned int accountNumber);
        bool validateUser(const std::string& login, unsigned int password);

        std::string personalCabinet(std::istream& input, std::ostream& output);
        std::string addFunds(double amount);
        std::string showBalance();
        std::string transferMoney(unsigned int toAccount, double amount);
        std::string logout();

        int getAccountCount() const;
        std::string getAllAccountsInfo() const;
    };
}