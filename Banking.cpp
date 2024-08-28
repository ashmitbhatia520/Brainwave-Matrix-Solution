#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    Account(int accNo, string name, double initialBalance) {
        accountNumber = accNo;
        accountHolder = name;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: ₹" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: ₹" << balance << endl;
            return true;
        } else {
            cout << "Invalid or insufficient funds for withdrawal." << endl;
            return false;
        }
    }

    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << ", Account Holder: " << accountHolder << ", Balance: ₹" << balance << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber = 1001;

    Account* findAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

public:
    void createAccount(const string& name, double initialDeposit) {
        if (initialDeposit < 0) {
            cout << "Initial deposit must be positive." << endl;
            return;
        }
        Account newAccount(nextAccountNumber++, name, initialDeposit);
        accounts.push_back(newAccount);
        cout << "Account created successfully with Account Number: " << newAccount.getAccountNumber() << endl;
    }

    void deposit(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->deposit(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void withdraw(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account) {
            account->withdraw(amount);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void transfer(int fromAccount, int toAccount, double amount) {
        Account* source = findAccount(fromAccount);
        Account* destination = findAccount(toAccount);
        if (!source) {
            cout << "Source account not found." << endl;
            return;
        }
        if (!destination) {
            cout << "Destination account not found." << endl;
            return;
        }
        if (source->withdraw(amount)) {
            destination->deposit(amount);
            cout << "Transfer successful." << endl;
        } else {
            cout << "Transfer failed due to insufficient funds." << endl;
        }
    }

    void displayAllAccounts() const {
        for (const auto &account : accounts) {
            account.displayAccountDetails();
        }
    }
};

int main() {
    Bank bank;
    int choice;
    while (true) {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Display All Accounts\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name;
                double initialDeposit;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter initial deposit: ";
                cin >> initialDeposit;
                bank.createAccount(name, initialDeposit);
                break;
            }
            case 2: {
                int accNo;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter deposit amount: ";
                cin >> amount;
                bank.deposit(accNo, amount);
                break;
            }
            case 3: {
                int accNo;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                bank.withdraw(accNo, amount);
                break;
            }
            case 4: {
                int fromAcc, toAcc;
                double amount;
                cout << "Enter source account number: ";
                cin >> fromAcc;
                cout << "Enter destination account number: ";
                cin >> toAcc;
                cout << "Enter transfer amount: ";
                cin >> amount;
                bank.transfer(fromAcc, toAcc, amount);
                break;
            }
            case 5:
                bank.displayAllAccounts();
                break;
            case 6:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
