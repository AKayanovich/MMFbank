#include <iostream>
#include <string>
#include "AccountDB.h"
#include <ctime>

using namespace mmfbank;
using namespace std;

int main() {
    srand(time(NULL));
    AccountDB bank(20);

    bank.addRandomAccount();
    bank.addRandomAccount();
    bank.addRandomAccount();
    bank.addRandomAccount();

    int choice;
    string login;
    unsigned int password;
    double balance;

    do {
        cout << "\n===== MMFBank =====\n";
        cout << "1. Show all accounts (debug)\n";
        cout << "2. Login\n";
        cout << "3. Register new account\n";
        cout << "4. Create random account\n";
        cout << "5. Exit\n";
        cout << "Choose action: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << bank.getAllAccountsInfo();
            break;

        case 2:
            cout << "Enter login: ";
            cin >> login;
            cout << "Enter password: ";
            cin >> password;

            if (bank.validateUser(login, password)) {
                cout << "Login successful!\n";
                string cabinetResult = bank.personalCabinet(cin, cout);
                cout << cabinetResult;
            }
            else {
                cout << "Invalid login or password\n";
            }
            break;

        case 3:
            cout << "Enter login for new account: ";
            cin >> login;
            cout << "Enter initial balance: ";
            cin >> balance;

            bank.addAccount(login, balance);
            cout << "Account created successfully\n";
            cout << "Your account number: " << (bank.getAccountCount() - 1 + 9000) << "\n";
            cout << "Your password: " << (bank.getAccountCount() - 1 + 9900) << "\n";
            break;

        case 4:
            bank.addRandomAccount();
            cout << "Random account created successfully!\n";
            cout << "Account number: " << (bank.getAccountCount() - 1 + 9000) << "\n";
            cout << "Password: " << (bank.getAccountCount() - 1 + 9900) << "\n";
            break;

        case 5:
            cout << "Thank you for using MMFBank!\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}