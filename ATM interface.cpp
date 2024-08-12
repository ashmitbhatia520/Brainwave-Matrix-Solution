#include <iostream>
#include <string>

using namespace std;

class ATM {
private:
    double balance;
    string accountNumber;
    string pin;

public:
    ATM(string accountNumber, string pin, double balance) {
        this->accountNumber = accountNumber;
        this->pin = pin;
        this->balance = balance;
    }

    void displayMenu() {
        cout << "Welcome to the ATM!" << endl;
        cout << "-------------------" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Withdraw Cash" << endl;
        cout << "3. Deposit Cash" << endl;
        cout << "4. Exit" << endl;
        cout << "-------------------" << endl;
    }

    void checkBalance() {
        cout << "Your current balance is: ₹" << balance << endl;
    }

    void withdrawCash() {
        double amount;
        cout << "Enter the amount to withdraw: ";
        cin >> amount;
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. Your new balance is: ₹" << balance << endl;
        }
    }

    void depositCash() {
        double amount;
        cout << "Enter the amount to deposit: ";
        cin >> amount;
        balance += amount;
        cout << "Deposit successful. Your new balance is: ₹" << balance << endl;
    }

    bool authenticate(string pin) {
        return this->pin == pin;
    }

    void run() {
        string inputPin;
        cout << "Enter your PIN: ";
        cin >> inputPin;
        if (authenticate(inputPin)) {
            int choice;
            do {
                displayMenu();
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        checkBalance();
                        break;
                    case 2:
                        withdrawCash();
                        break;
                    case 3:
                        depositCash();
                        break;
                    case 4:
                        cout << "Thank you for using the ATM!" << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 4);
        } else {
            cout << "Invalid PIN. Please try again." << endl;
        }
    }
};

int main() {
    ATM atm("123456", "1234", 1000.0);
    atm.run();
    return 0;
}
