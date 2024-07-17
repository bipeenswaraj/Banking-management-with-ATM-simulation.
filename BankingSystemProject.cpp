#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// ACCOUNT CLASS
class Account
{
public:
    string accountnumber;
    string name;
    string password;
    double initialDeposit;
    double cBalance;

    Account(string an, string nm, string p, double b)
        : accountnumber(an), name(nm), password(p), cBalance(b) {}

    Account()
    {
        accountnumber = "unknown";
        name = "Unknown";
        password = "unknown";
        cBalance = 0;
    }

    void setInfo(string n, string p, string q, double r)
    {
        accountnumber = n;
        name = p;
        password = q;
        initialDeposit = r;
        cBalance = r;
    }

    void getInfo() const
    {
        cout << "account Information:" << endl;
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountnumber << endl;
        cout << "Password: XXXXXXXX" << endl;
        cout << "Current Balance: " << cBalance << endl;
    }
    void initialdpst(Account &user)
    {
        double initialDeposit;
        cout << "Initial deposit (0 - 1000) :  ";
        cin >> initialDeposit;
        if (initialDeposit >= 0)
        {
            user.cBalance += initialDeposit;
        }
        else
        {
            cout << "invalid input" << endl;
        }
    }
};
// ACCOUNT MANAGEMENT CLASS
class AccountManager
{
private:
    vector<Account> accounts;
    static int currentAccountNumber; // Static variable for account number

public:
    AccountManager()
    {
        currentAccountNumber = 12004; // Initial account number
    }

    void insertAccount(const string &accNum, const string &name, const string &pwd, double bal)
    {
        Account newAccount(accNum, name, pwd, bal);
        accounts.push_back(newAccount);
        sort(accounts.begin(), accounts.end(), [](const Account &a, const Account &b)
             { return a.accountnumber < b.accountnumber; });
    }

    string insertNewAccount(const string &name, const string &pwd, double bal)
    {
        string accNum = to_string(currentAccountNumber++);
        Account newAccount(accNum, name, pwd, bal);
        accounts.push_back(newAccount);
        return accNum; // Return the newly generated account number
    }
    Account *searchAccount(const string &accNum)
    {
        for (auto &account : accounts)
        {
            if (account.accountnumber == accNum)
            {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAllAccounts() const
    {
        for (const auto &account : accounts)
        {
            account.getInfo();
        }
    }
};
int AccountManager::currentAccountNumber = 12004;

// ATM CLASS

class ATMOperations
{
public:
    void deposit(Account &user)
    {
        double amount;
        cout << "Enter money you want to deposit: " << endl;
        cin >> amount;
        if (amount > 0)
        {
            user.cBalance += amount;
            cout << "Amount of " << amount << " deposited successfully" << endl;
        }
        else
        {
            cout << "Invalid amount" << endl;
        }
    }

    void withdraw(Account &user)
    {
        double wBalance;
        cout << "Your current balance is " << user.cBalance << endl;
        cout << "Enter money you want to withdraw: " << endl;
        cin >> wBalance;
        if (wBalance <= user.cBalance)
        {
            user.cBalance -= wBalance;
            cout << "Money withdrawal successful." << endl;
        }
        else
        {
            cout << " balance in your account is insufficient." << endl;
        }
    }
};
// SECURITY CLASS
class SecurityAuthentication
{
public:
    bool authenticate(Account &user, string inputPsd)
    {
        return user.password == inputPsd;
    }
};

// BANK TRANSACTIONS CLASS
class BankingTransactions
{
public:
    void deposit(Account &user)
    {
        ATMOperations atm;
        atm.deposit(user);
    }

    void withdraw(Account &user, SecurityAuthentication &security)
    {
        ATMOperations atm;
        string Password;
        cout << "Enter your password: ";
        cin >> Password;
        if (security.authenticate(user, Password))
        {
            atm.withdraw(user);
        }
        else
        {
            cout << "Wrong password .try again." << endl;
        }
    }
};

int main()
{
    Account user;
    BankingTransactions transactions;
    SecurityAuthentication security;
    AccountManager manager;

    string accountnumber;
    string name;
    string password;
    double initialDeposit;
    string currentAccountNumber;
    int choice1, choice2, choice3, choice4;

    // Inserting accounts
    manager.insertAccount("12001", "Bipeen", "pass101", 500);
    manager.insertAccount("12002", "Sameer", "pass201", 400.0);
    manager.insertAccount("12003", "Ranjay", "pass301", 1000.0);
    do
    {
        cout << " \n Log in as:\n (1) CUSTOMER\n (2) MANAGER\n (3) EXIT APPLICATION" << endl;
        cin >> choice3;
        switch (choice3)
        {
        case 1:
        {

            do
            {
                cout << "\nWelcome to National Smart Bank (NSB).\n"
                     << endl
                     << "To use services, kindly provide your correct credentials:" << endl;
                cout << "\nSelect an option to proceed: " << endl;
                cout << "1. Log in by Account number\n2. Create new account\n3.  ATM service" << endl;
                cin >> choice1;

                switch (choice1)
                {
                case 1:
                {
                    cout << "Enter your account number: ";
                    cin >> accountnumber;
                    Account *account = manager.searchAccount(accountnumber);
                    if (account)
                    {
                        cout << "Account found: " << endl;
                        user = *account;
                    }
                    else
                    {
                        cout << "Account not found." << endl;
                        break;
                    }
                    break;
                }
                case 2:
                {
                    cout << "Enter your name: ";
                    cin >> name;
                    cout << "Create password: ";
                    cin >> password;
                    cout << "Initial deposit: ";
                    cin >> initialDeposit;
                    string newAccountNumber = manager.insertNewAccount(name, password, initialDeposit);
                    user.setInfo(newAccountNumber, name, password, initialDeposit);
                    cout << "Account opened successfully" << endl;
                    cout << "your new account number is " << newAccountNumber << endl;
                    break;
                }
                case 3:
                {
                    cout << "Account verification completed; you are eligible for ATM services." << endl;
                    break;
                }
                default:
                {
                    cout << "Invalid option. Please enter a number from 1 to 3." << endl;
                    break;
                }
                }
            } while (choice1 != 3);

            do
            {
                cout << "\nSelect an option to proceed: \n"
                     << endl;
                cout << "(1) Deposit money                          (2) Withdraw money\n(3) Display passbook                       (4) Exit" << endl;
                cin >> choice2;

                switch (choice2)
                {
                case 1:
                    transactions.deposit(user);
                    break;
                case 2:
                    transactions.withdraw(user, security);
                    break;
                case 3:
                    user.getInfo();
                    break;
                case 4:
                    cout << "Exiting ATM. Have a nice day!" << endl;
                    break;
                default:
                    cout << "Invalid option. Please enter a number from 1 to 4." << endl;
                    break;
                }
            } while (choice2 != 4);
        }
        break;
        case 2:
        {
            string sc;
            string securitycode = "2943ab";
            cout << "Hello manager,confirm your identity to proceed.\n"
                 << endl;
            cout << "Enter  6 digit Security code: " << endl;
            cin >> sc;
            if (sc == securitycode)
            {
                cout << "You are logged in." << endl;
                do
                {
                    cout << "\n(1) Search account\n(2) Display all accounts\n(3) Log out\n";
                    cin >> choice4;
                    switch (choice4)
                    {
                    case 1:
                    {
                        string akn;
                        cout << "Enter account number: ";
                        cin >> akn;
                        Account *foundAccount = manager.searchAccount(akn);
                        if (foundAccount != nullptr)
                        {
                            cout << "Account found: " << foundAccount->accountnumber << endl;
                            cout << "Account holder name: " << foundAccount->name << endl;
                            cout << "Account balance: " << foundAccount->cBalance << endl;
                        }
                        else
                        {
                            cout << "Account not found." << endl;
                        }
                        break;
                    }
                    case 2:
                        manager.displayAllAccounts();
                        break;
                    case 3:
                        cout << "Logged out." << endl;
                        break;
                    default:
                        cout << "Invalid option. Please enter a number from 1 to 3." << endl;
                    }
                } while (choice4 != 3);
            }
            else
            {
                cout << "Wrong code.try again." << endl;
            }
            break;
        }
        break;
        case 3:
        {
            cout << "Exiting the application.|| visit again ||" << endl;
            break;
        }
        default:
            cout << "Invalid option. Please enter a number from 1 to 3.";
        }

    } while (choice3 != 3);
    return 0;
}
