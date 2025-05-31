#include "AccountDB.h"
#include <iostream>
#include <sstream>

namespace mmfbank {
    AccountDB::AccountDB(int amount) : accountCount(0), currentUserIndex(-1) {
        accounts = new Account[amount];
    }

    AccountDB::~AccountDB() {
        delete[] accounts;
    }

    void AccountDB::addAccount(const std::string& login, double balance) {
        unsigned int accountNumber = accountCount + 9000;
        unsigned int password = accountCount + 9900;

        Account* newAccounts = new Account[accountCount + 1];

        for (int i = 0; i < accountCount; i++) {
            newAccounts[i] = accounts[i];
        }

        newAccounts[accountCount] = Account(login, accountNumber, balance, password);

        delete[] accounts;
        accounts = newAccounts;
        accountCount++;
    }

    void AccountDB::addRandomAccount() {
        Account* newAccounts = new Account[accountCount + 1];

        for (int i = 0; i < accountCount; i++) {
            newAccounts[i] = accounts[i];
        }

        newAccounts[accountCount] = Account::generateRandomAccount(accountCount);

        delete[] accounts;
        accounts = newAccounts;
        accountCount++;
    }

    Account* AccountDB::searchByLogin(const std::string& login) {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].getLogin() == login) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    Account* AccountDB::searchByNumber(unsigned int accountNumber) {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    bool AccountDB::validateUser(const std::string& login, unsigned int password) {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].getLogin() == login && accounts[i].validatePassword(password)) {
                currentUserIndex = i;
                return true;
            }
        }
        return false;
    }

    std::string AccountDB::personalCabinet(std::istream& input, std::ostream& output) {
        if (currentUserIndex == -1) {
            return "Access denied - user not logged in";
        }

        int choice;
        std::ostringstream result;

        do {
            output << "\n===== Personal Cabinet =====\n";
            output << "Current user: " << accounts[currentUserIndex].getLogin() << "\n";
            output << "1. Add funds\n";
            output << "2. Show balance\n";
            output << "3. Transfer money\n";
            output << "4. Logout\n";
            output << "5. Exit\n";
            output << "Choose action: ";
            input >> choice;

            switch (choice) {
            case 1: {
                double amount;
                output << "Enter amount to add: ";
                input >> amount;
                std::string addResult = addFunds(amount);
                output << addResult << "\n"; 
                result << addResult << "\n"; 
                break;
            }
            case 2: {
                std::string balanceResult = showBalance();
                output << balanceResult << "\n"; 
                result << balanceResult << "\n";
                break;
            }
            case 3: {
                unsigned int toAccount;
                double amount;
                output << "Enter recipient account number: ";
                input >> toAccount;
                output << "Enter amount to transfer: ";
                input >> amount;
                std::string transferResult = transferMoney(toAccount, amount);
                output << transferResult << "\n"; 
                result << transferResult << "\n";
                break;
            }
            case 4:
                result << logout();
                return result.str();
            case 5:
                return result.str();
            default:
                result << "Invalid choice\n";
            }
        } while (choice != 5);

        return result.str();
    }

    std::string AccountDB::addFunds(double amount) {
        accounts[currentUserIndex].addFunds(amount);
        return "Funds added successfully";
    }

    std::string AccountDB::showBalance() {
        std::ostringstream oss;
        oss << "Current balance: $" << accounts[currentUserIndex].getBalance();
        return oss.str();
    }

    std::string AccountDB::transferMoney(unsigned int toAccount, double amount) {
        if (accounts[currentUserIndex].getAccountNumber() == toAccount) {
            return "Cannot transfer to same account";
        }

        Account* receiver = searchByNumber(toAccount);
        if (!receiver) {
            return "Receiver account not found";
        }

        try {
            accounts[currentUserIndex].withdrawFunds(amount);
            receiver->addFunds(amount);
            return "Transfer successful";
        }
        catch (const char* error) {
            std::ostringstream oss;
            oss << "Transfer failed: " << error;
            return oss.str();
        }
    }

    std::string AccountDB::logout() {
        currentUserIndex = -1;
        return "Logged out successfully";
    }

    int AccountDB::getAccountCount() const {
        return accountCount;
    }

    std::string AccountDB::getAllAccountsInfo() const {
        std::ostringstream oss;
        oss << "\n===== All Accounts =====\n";
        for (int i = 0; i < accountCount; i++) {
            oss << accounts[i] << "Password: " << (i + 9900) << "\n\n";
        }
        return oss.str();
    }
}