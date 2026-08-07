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

// Function Prototypes
void showMenu();

void createAccount();
void viewAccounts();

void depositMoney();
void withdrawMoney();
void checkBalance();
void searchAccount();
void saveAccounts();
void deleteAccount();
void addTransaction(int accountNumber, string type, double amount);
void viewTransactions();
void loadAccounts();

BankAccount *findAccount(int accountNumber);

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
    cout << "6. Search Account\n";
    cout << "7. Delete Account\n";
    cout << "8. Transaction History\n";
    cout << "9. Exit\n";

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

    cout << "\n===== DEPOSIT MONEY =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    BankAccount *acc = findAccount(accountNumber);

    if (acc == nullptr)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Current Balance: Rs. " << acc->balance << endl;

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid Amount!\n";
        return;
    }

    acc->balance += amount;

    addTransaction(
        acc->accountNumber,
        "Deposit",
        amount);

    saveAccounts();

    cout << "\nDeposit Successful!\n";
    cout << "Updated Balance: Rs. " << acc->balance << endl;
}

void withdrawMoney()
{
    int accountNumber;
    double amount;

    cout << "\n===== WITHDRAW MONEY =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    BankAccount *acc = findAccount(accountNumber);

    if (acc == nullptr)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Current Balance: Rs. " << acc->balance << endl;

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid Amount!\n";
        return;
    }

    if (amount > acc->balance)
    {
        cout << "Insufficient Balance!\n";
        return;
    }

    acc->balance -= amount;

    addTransaction(
        acc->accountNumber,
        "Withdraw",
        amount);

    saveAccounts();

    cout << "\nWithdrawal Successful!\n";
    cout << "Remaining Balance: Rs. " << acc->balance << endl;
}

void checkBalance()
{
    int accountNumber;

    cout << "\n===== CHECK BALANCE =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    BankAccount *acc = findAccount(accountNumber);

    if (acc == nullptr)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "\nAccount Holder : " << acc->name << endl;
    cout << "Current Balance: Rs. " << acc->balance << endl;
}

void searchAccount()
{
    int accountNumber;

    cout << "\n===== SEARCH ACCOUNT =====\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    BankAccount *acc = findAccount(accountNumber);

    if (acc == nullptr)
    {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "\n========== ACCOUNT DETAILS ==========\n";
    cout << "Account Number : " << acc->accountNumber << endl;
    cout << "Account Holder : " << acc->name << endl;
    cout << "Balance        : Rs. " << acc->balance << endl;
}

void deleteAccount()
{
    int accountNumber;

    cout << "\n===== DELETE ACCOUNT =====\n";
    cout << "Enter Account Number: ";
    cin >> accountNumber;

    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            char choice;

            cout << "Account Holder: " << accounts[i].name << endl;
            cout << "Balance: Rs. " << accounts[i].balance << endl;

            cout << "\nAre you sure you want to delete this account? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                accounts.erase(accounts.begin() + i);

                saveAccounts();

                cout << "\nAccount Deleted Successfully!\n";
            }
            else
            {
                cout << "\nDeletion Cancelled.\n";
            }

            return;
        }
    }

    cout << "Account Not Found!\n";
}

void viewTransactions()
{
    cout << "\nOpening transactions...\n";

    ifstream file("transactions.txt");

    if (!file)
    {
        cout << "No Transactions Found!\n";
        return;
    }
    
    cout << "File Opened Successfully!\n";

    cout << "\n========== TRANSACTION HISTORY ==========\n\n";

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
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

void addTransaction(int accountNumber, string type, double amount)
{
    ofstream file("transactions.txt", ios::app);

    if (!file)
    {
        cout << "Error Opening Transaction File!\n";
        return;
    }

    file << "==================================\n";
    file << "Account Number : " << accountNumber << endl;
    file << "Transaction    : " << type << endl;
    file << "Amount         : Rs. " << amount << endl;
    file << "==================================\n\n";

    file.close();

    cout << "Transaction Logged!\n";
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

BankAccount *findAccount(int accountNumber)
{
    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accountNumber)
        {
            return &acc;
        }
    }

    return nullptr;
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
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            viewAccounts();
            break;

        case 6:
            searchAccount();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            viewTransactions();
            break;

        case 9:
            cout << "\nThank you for using the Banking Management System.\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}