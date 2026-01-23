#include<bits/stdc++.h>
using namespace std;
class Account
{
private:
    int balance, pin, weeklyWithdrawn;
    static const int minBal = 500;
    static const int weeklyLimit = 10000;
public:
    // Constructor
    Account(int b, int p)
    {
        if(b >= minBal)
            balance=b;
        else
            balance=minBal;
        pin = p;
        weeklyWithdrawn = 0;
    }

    // PIN verification
    bool pinVerify(int enteredPin)
    {
        return enteredPin == pin;
    }

    // Deposit
    void deposit(int amount)
    {
        if(amount > 0)
        {
            balance += amount;
            cout<<"Deposited successfully!!"<<endl;
        }
        else
        {
            cout<<"Invalid deposit amount! TRY AGAIN..."<<endl;
        }
    }

    // Withdraw
    void withdraw(int amount, int enteredPin)
    {
        if(!pinVerify(enteredPin))
        {
            cout<<"Incorrect PIN!!"<<endl;
            return;
        }
        if(amount <= 0)
        {
            cout<<"Invalid amount!!"<<endl;
            return;
        }
        if(amount > weeklyLimit)
        {
            cout<<"Weekly withdraw limit exceeded!!"<<endl;
            return;
        }
        if (balance - amount < minBal)
        {
            cout<<"Minimum balance (500) must be maintained!!"<<endl;
            return;
        }
        balance -= amount;
        weeklyWithdrawn += amount;
        cout<<"Withdraw successful!"<<endl;
    }
    void showBalance()
    {
        cout<<"Current Balance = "<<balance<<endl;
    }
    void showWeeklyWithdraw()
    {
        cout<<"Withdrawn this week = "<<weeklyWithdrawn<<endl;
    }
};
int main()
{
    int initialBalance, pin;
    cout<<"Enter initial balance = ";
    cin >> initialBalance;
    cout<<"Set your 4-digit PIN = ";
    cin >> pin;
    Account acc(initialBalance, pin);
    int choice;
    while(true)
    {
        cout<<"\n**** MENU ****\n";
        cout<<"1. Deposit\n";
        cout<<"2. Withdraw\n";
        cout<<"3. Check Balance\n";
        cout<<"4. Weekly Withdraw Info\n";
        cout<<"5. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
        if(choice == 1)
        {
            int amn;
            cout<<"Enter deposit amount = ";
            cin>>amn;
            acc.deposit(amn);
        }
        else if(choice == 2)
        {
            int amn, enteredPin;
            cout<<"Enter withdraw amount = ";
            cin>>amn;
            cout<<"Enter PIN = ";
            cin>>enteredPin;
            acc.withdraw(amn, enteredPin);
        }
        else if(choice == 3)
        {
            acc.showBalance();
        }
        else if(choice == 4)
        {
            acc.showWeeklyWithdraw();
        }
        else if(choice == 5)
        {
            cout<<"Thank you! Program ended."<<endl;
            break;
        }
        else
        {
            cout<<"Invalid choice!"<<endl;
        }
    }
    return 0;
}

