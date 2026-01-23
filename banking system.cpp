#include <bits/stdc++.h>
using namespace std;
class Account
{
private:
    int balance;

public:
    // constructor
    Account(int b)
    {
        if (b >= 0)
        {
            balance = b;
        }
        else
        {
            balance = 0;
        }
    }

    // deposit money
    void deposit(int amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited successfully!!" << endl;
        }
        else
        {
            cout << "Invalid deposit amount. Please try again" << endl;
        }
    }

    // withdraw money
    void withdraw(int amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawn Successfully!!" << endl;
        }
        else
        {
            cout << "Invalid amount for withdaw." << endl;
        }
    }
    int getBalance()
    {
        return balance;
    }
};
int main()
{
    int mainBal;
    cout << "Give your Amount: ";
    cin >> mainBal;
    Account acc(mainBal);
    int choice;
    while (true)
    {
        cout << "\n**** MENU ****\n";
        cout << "1. Deposit" << endl;
        cout << "2. Withdaraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Your Choice--> ";
        cin >> choice;
        if (choice == 1)
        {
            int amount;
            cout << "Enter deposit amount = ";
            cin >> amount;
            acc.deposit(amount);
        }
        else if (choice == 2)
        {
            int amount;
            cout << "Enter Withdaraw amount = ";
            cin >> amount;
            acc.withdraw(amount);
        }
        else if (choice == 3)
        {
            cout << "Your current Balance = " << acc.getBalance() << endl;
        }
        else if (choice == 4)
        {
            cout << "Thank you, Sir/Madam..";
            break;
        }
        else
        {
            cout << "Invalid choice!! Try again...";
        }
    }
    return 0;
}
