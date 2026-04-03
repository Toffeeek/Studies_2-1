#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Bank;
class Account;

//=========================== Transaction Class ===========================//
class Transaction
{
private:
    string type; // Deposit / Withdraw / Transfer
    double amount;
    string details;

public:
    Transaction(string type = "", double amount = 0, string details = "")
        : type(type), amount(amount), details(details) {}

    string getType() const { return type; }
    double getAmount() const { return amount; }
    string getDetails() const { return details; }

    void display() const
    {
        cout << left << setw(12) << type
             << setw(12) << amount
             << details << endl;
    }
};

//=========================== Abstract Account Class ===========================//
class Account
{
protected:
    string holderName;
    string accountNumber;
    double balance;
    bool frozen;
    vector<Transaction *> transactionHistory;

public:
    Account(string holderName, string accountNumber, double balance = 0.0)
        : holderName(holderName), accountNumber(accountNumber),
          balance(balance), frozen(false) {}

    virtual ~Account() {}

    string getHolderName() const { return holderName; }
    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    bool isFrozen() const { return frozen; }

    void freezeAccount() { frozen = true; }

    void addTransaction(Transaction *t)
    {
        transactionHistory.push_back(t);
    }

    const vector<Transaction *> &getTransactions() const
    {
        return transactionHistory;
    }

    virtual string getAccountType() const = 0;

    virtual bool deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;

    virtual void resetDailyLimit() {}

    virtual void displayAccountInfo() const
    {
        cout << "Account Type   : " << getAccountType() << endl;
        cout << "Holder Name    : " << holderName << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Balance        : " << balance << endl;
        cout << "Frozen         : " << (frozen ? "Yes" : "No") << endl;
    }

    void displayTransactionHistory() const
    {
        cout << "\nTransaction history for Account " << accountNumber << ":\n";
        if (transactionHistory.empty())
        {
            cout << "No transaction found.\n";
            return;
        }

        cout << left << setw(12) << "Type"
             << setw(12) << "Amount"
             << "Details" << endl;

        for (auto t : transactionHistory)
        {
            t->display();
        }
    }
};

//=========================== Current Account ===========================//
class CurrentAccount : public Account
{
private:
    static constexpr double yearlyMaintenanceFee = 1000.0;

public:
    CurrentAccount(string holderName, string accountNumber, double balance = 0.0)
        : Account(holderName, accountNumber, balance) {}

    string getAccountType() const override
    {
        return "Current";
    }

    bool deposit(double amount) override
    {
        if (frozen || amount <= 0)
            return false;

        balance += amount;
        addTransaction(new Transaction("Deposit", amount, "Deposited to current account"));
        return true;
    }

    bool withdraw(double amount) override
    {
        if (frozen || amount <= 0)
            return false;
        if (balance - amount < 0)
            return false;

        balance -= amount;
        addTransaction(new Transaction("Withdraw", amount, "Withdrawn from current account"));
        return true;
    }

    double getYearlyMaintenanceFee() const
    {
        return yearlyMaintenanceFee;
    }
};

//=========================== Savings Account ===========================//
class SavingsAccount : public Account
{
private:
    int freeWithdrawalsPerDay;
    int freeDepositsPerDay;
    double dailyWithdrawalLimit;

    int todayWithdrawalCount;
    int todayDepositCount;
    double todayWithdrawnAmount;

public:
    SavingsAccount(string holderName, string accountNumber, double balance = 0.0,
                   int freeWithdrawalsPerDay = 5, int freeDepositsPerDay = 5,
                   double dailyWithdrawalLimit = 10000.0)
        : Account(holderName, accountNumber, balance),
          freeWithdrawalsPerDay(freeWithdrawalsPerDay),
          freeDepositsPerDay(freeDepositsPerDay),
          dailyWithdrawalLimit(dailyWithdrawalLimit),
          todayWithdrawalCount(0), todayDepositCount(0),
          todayWithdrawnAmount(0.0) {}

    string getAccountType() const override
    {
        return "Savings";
    }

    void resetDailyLimit() override
    {
        todayWithdrawalCount = 0;
        todayDepositCount = 0;
        todayWithdrawnAmount = 0.0;
    }

    double calculateWithdrawalFee(double amount) const
    {
        if (todayWithdrawalCount < freeWithdrawalsPerDay &&
            todayWithdrawnAmount + amount <= dailyWithdrawalLimit)
        {
            return 0.0;
        }

        double fee1 = 100.0;
        double fee2 = amount * 0.02;
        return (fee1 > fee2) ? fee1 : fee2;
    }

    bool deposit(double amount) override
    {
        if (frozen || amount <= 0)
            return false;

        balance += amount;
        todayDepositCount++;

        string details = "Deposited to savings account";
        if (todayDepositCount > freeDepositsPerDay)
            details += " (deposit count exceeded free daily limit, but no fee specified)";

        addTransaction(new Transaction("Deposit", amount, details));
        return true;
    }

    bool withdraw(double amount) override
    {
        if (frozen || amount <= 0)
            return false;

        double fee = calculateWithdrawalFee(amount);
        double totalDeduction = amount + fee;

        if (balance - totalDeduction < 0)
            return false;

        balance -= totalDeduction;
        todayWithdrawalCount++;
        todayWithdrawnAmount += amount;

        string details = "Withdrawn from savings account";
        if (fee > 0)
        {
            details += ", Fee applied: " + to_string(fee);
        }

        addTransaction(new Transaction("Withdraw", amount, details));
        return true;
    }

    int getFreeWithdrawalsPerDay() const { return freeWithdrawalsPerDay; }
    int getFreeDepositsPerDay() const { return freeDepositsPerDay; }
    double getDailyWithdrawalLimit() const { return dailyWithdrawalLimit; }

    void displayAccountInfo() const override
    {
        Account::displayAccountInfo();
        cout << "Free Withdrawals/Day : " << freeWithdrawalsPerDay << endl;
        cout << "Free Deposits/Day    : " << freeDepositsPerDay << endl;
        cout << "Daily Withdraw Limit : " << dailyWithdrawalLimit << endl;
        cout << "Today's Withdrawals  : " << todayWithdrawalCount << endl;
        cout << "Today's Deposits     : " << todayDepositCount << endl;
        cout << "Today's Withdraw Amt : " << todayWithdrawnAmount << endl;
    }
};

//=========================== Bank Class ===========================//
class Bank
{
private:
    string bankName;
    vector<Account *> accounts;
    vector<Transaction *> bankTransactions;

    Account *findAccount(const string &accNo) const
    {
        for (auto acc : accounts)
        {
            if (acc->getAccountNumber() == accNo)
                return acc;
        }
        return nullptr;
    }

public:
    Bank(string name = "") : bankName(name) {}

    ~Bank()
    {
        // delete all accounts
        for (auto acc : accounts)
        {
            delete acc;
        }

        // delete all bank transaction objects
        for (auto t : bankTransactions)
        {
            delete t;
        }
    }

    void addAccount(Account *acc)
    {
        accounts.push_back(acc);
    }

    void removeAccount(const string &accNo)
    {
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
        {
            if ((*it)->getAccountNumber() == accNo)
            {
                delete *it;
                accounts.erase(it);
                cout << "Account " << accNo << " removed from bank.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    bool depositToAccount(const string &accNo, double amount)
    {
        Account *acc = findAccount(accNo);
        if (!acc)
        {
            cout << "Account not found.\n";
            return false;
        }

        bool success = acc->deposit(amount);
        if (success)
        {
            bankTransactions.push_back(
                new Transaction("Deposit", amount, "Deposit to account " + accNo));
            cout << "Deposit successful.\n";
        }
        else
        {
            cout << "Deposit failed.\n";
        }
        return success;
    }

    bool withdrawFromAccount(const string &accNo, double amount)
    {
        Account *acc = findAccount(accNo);
        if (!acc)
        {
            cout << "Account not found.\n";
            return false;
        }

        bool success = acc->withdraw(amount);
        if (success)
        {
            bankTransactions.push_back(
                new Transaction("Withdraw", amount, "Withdraw from account " + accNo));
            cout << "Withdrawal successful.\n";
        }
        else
        {
            cout << "Withdrawal failed.\n";
        }
        return success;
    }

    bool transferFunds(const string &fromAcc, const string &toAcc, double amount)
    {
        Account *sender = findAccount(fromAcc);
        Account *receiver = findAccount(toAcc);

        if (!sender || !receiver)
        {
            cout << "One or both accounts not found.\n";
            return false;
        }

        if (sender->isFrozen() || receiver->isFrozen())
        {
            cout << "Transfer not allowed. One of the accounts is frozen.\n";
            return false;
        }

        bool withdrawn = sender->withdraw(amount);
        if (!withdrawn)
        {
            cout << "Transfer failed during withdrawal from sender account.\n";
            return false;
        }

        bool deposited = receiver->deposit(amount);
        if (!deposited)
        {
            // rollback attempt
            sender->deposit(amount);
            cout << "Transfer failed during deposit to receiver account.\n";
            return false;
        }

        sender->addTransaction(new Transaction("Transfer", amount,
                                               "Transferred to account " + toAcc));
        receiver->addTransaction(new Transaction("Transfer", amount,
                                                 "Received from account " + fromAcc));

        bankTransactions.push_back(
            new Transaction("Transfer", amount,
                            "From " + fromAcc + " to " + toAcc));

        cout << "Transfer successful.\n";
        return true;
    }

    void clearDailyLimitAllAccounts()
    {
        for (auto acc : accounts)
        {
            acc->resetDailyLimit();
        }
        cout << "Daily limits cleared for all accounts.\n";
    }

    void printAllTransactionHistories() const
    {
        cout << "\n========== ALL ACCOUNT TRANSACTION HISTORIES ==========\n";
        for (auto acc : accounts)
        {
            acc->displayTransactionHistory();
            cout << endl;
        }
    }

    void printBankTransactions() const
    {
        cout << "\n========== BANK TRANSACTIONS ==========\n";
        if (bankTransactions.empty())
        {
            cout << "No bank transactions found.\n";
            return;
        }

        cout << left << setw(12) << "Type"
             << setw(12) << "Amount"
             << "Details" << endl;

        for (auto t : bankTransactions)
        {
            t->display();
        }
    }

    void printAllCurrentBalances() const
    {
        cout << "\n========== CURRENT BALANCES ==========\n";
        for (auto acc : accounts)
        {
            cout << "Account No: " << acc->getAccountNumber()
                 << ", Holder: " << acc->getHolderName()
                 << ", Type: " << acc->getAccountType()
                 << ", Balance: " << acc->getBalance();

            if (acc->isFrozen())
                cout << " [FROZEN]";
            cout << endl;
        }
    }

    void displayAllAccounts() const
    {
        cout << "\n========== ACCOUNT DETAILS ==========\n";
        for (auto acc : accounts)
        {
            acc->displayAccountInfo();
            cout << "-------------------------------------\n";
        }
    }
};

//=========================== Main Function ===========================//
int main()
{
    Bank bank("ABC Bank");

    Account *a1 = new CurrentAccount("Tawfiq", "C101", 20000);
    Account *a2 = new SavingsAccount("Rahim", "S201", 15000);
    Account *a3 = new SavingsAccount("Karim", "S202", 8000, 3, 4, 5000);

    bank.addAccount(a1);
    bank.addAccount(a2);
    bank.addAccount(a3);

    bank.displayAllAccounts();

    cout << "\n===== Performing Transactions =====\n";
    bank.depositToAccount("C101", 5000);
    bank.withdrawFromAccount("C101", 3000);

    bank.depositToAccount("S201", 2000);
    bank.withdrawFromAccount("S201", 3000);
    bank.withdrawFromAccount("S201", 2500);
    bank.withdrawFromAccount("S201", 2000);
    bank.withdrawFromAccount("S201", 1500);
    bank.withdrawFromAccount("S201", 1000);
    bank.withdrawFromAccount("S201", 500); // fee may apply

    bank.transferFunds("S201", "C101", 2000);

    cout << "\n===== Balances After Transactions =====\n";
    bank.printAllCurrentBalances();

    bank.printAllTransactionHistories();
    bank.printBankTransactions();

    cout << "\n===== Resetting Daily Limits =====\n";
    bank.clearDailyLimitAllAccounts();

    cout << "\n===== Removing Account S202 =====\n";
    bank.removeAccount("S202");

    cout << "\n===== Final Bank State =====\n";
    bank.printAllCurrentBalances();

    return 0;
}