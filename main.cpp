#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class BankAccount
{
public:
    int accountNumber;
    string name;
    double balance;

    BankAccount(int accNo, string accName, double initialBalance)
    {
        accountNumber = accNo;
        name = accName;
        balance = initialBalance;
    }
};

vector<BankAccount> accounts;

void showMenu()
{
    cout << "\n=============================\n";
    cout << "   BANK MANAGEMENT SYSTEM\n";
    cout << "=============================\n";

    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. View All Accounts\n";
    cout << "6. Exit\n";

    cout << "\nEnter your choice: ";
}

void createAccount()
{
    int accountNumber;
    string name;
    double balance;

    cout << "\n===== Create New Account =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    // Check if account number already exists
    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accountNumber)
        {
            cout << "Account Number already exists!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Deposit: ";
    cin >> balance;

    if (balance < 0)
    {
        cout << "Initial balance cannot be negative.\n";
        return;
    }

    BankAccount newAccount(accountNumber, name, balance);

    accounts.push_back(newAccount);

    cout << "\nAccount Created Successfully!\n";
}

void viewAccounts()
{
    if (accounts.empty())
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    cout << "\n========== All Accounts ==========\n";

    for (auto &acc : accounts)
    {
        cout << "Account Number : " << acc.accountNumber << endl;
        cout << "Name           : " << acc.name << endl;
        cout << "Balance        : Rs. " << acc.balance << endl;
        cout << "----------------------------------\n";
    }
}

void depositMoney()
{
    int accountNumber;
    double amount;

    cout << "\n===== Deposit Money =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accountNumber)
        {
            cout << "Current Balance: Rs. " << acc.balance << endl;

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            if (amount <= 0)
            {
                cout << "Invalid Amount!\n";
                return;
            }

            acc.balance += amount;

            cout << "\nAmount Deposited Successfully!\n";
            cout << "Updated Balance: Rs. " << acc.balance << endl;

            return;
        }
    }

    cout << "Account Not Found!\n";
}

void withdrawMoney()
{
    int accountNumber;
    double amount;

    cout << "\n===== Withdraw Money =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accountNumber)
        {
            cout << "Current Balance: Rs. " << acc.balance << endl;

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount <= 0)
            {
                cout << "Invalid Amount!\n";
                return;
            }

            if (amount > acc.balance)
            {
                cout << "Insufficient Balance!\n";
                return;
            }

            acc.balance -= amount;

            cout << "\nWithdrawal Successful!\n";
            cout << "Remaining Balance: Rs. " << acc.balance << endl;

            return;
        }
    }

    cout << "Account Not Found!\n";
}

void checkBalance()
{
    int accountNumber;

    cout << "\n===== Check Balance =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accountNumber)
        {
            cout << "\nAccount Holder : " << acc.name << endl;
            cout << "Current Balance: Rs. " << acc.balance << endl;
            return;
        }
    }

    cout << "Account Not Found!\n";
}

void saveAccounts()
{
    ofstream file("accounts.txt");

    if (!file)
    {
        cout << "Error saving file!\n";
        return;
    }

    for (auto &acc : accounts)
    {
        file << acc.accountNumber << ","
             << acc.name << ","
             << acc.balance << endl;
    }

    file.close();
}

void loadAccounts()
{
    ifstream file("accounts.txt");

    if (!file)
        return;

    accounts.clear();

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string accNo, name, balance;

        getline(ss, accNo, ',');
        getline(ss, name, ',');
        getline(ss, balance);

        BankAccount account(
            stoi(accNo),
            name,
            stod(balance));

        accounts.push_back(account);
    }

    file.close();
}

int main()
{
    loadAccounts();

    int choice;

    do
    {
        showMenu();

        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            saveAccounts();
            break;

        case 2:
            depositMoney();
            saveAccounts();
            break;

        case 3:
            withdrawMoney();
            saveAccounts();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            viewAccounts();
            break;

        case 6:
            cout << "\nThank you for using the Banking System.\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}