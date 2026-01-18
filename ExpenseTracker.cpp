#include "ExpenseTracker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

ExpenseTracker::ExpenseTracker() {
    loadFromFile();
}

void ExpenseTracker::addTransaction(const Transaction& t) {
    transactions.push_back(t);
    saveToFile();
}

void ExpenseTracker::showAll() const {
    cout << "\n--- All Transactions ---\n";
    for (const auto& t : transactions) {
        t.display();
    }
}

void ExpenseTracker::showBalance() const {
    double income = 0, expense = 0;

    for (const auto& t : transactions) {
        if (t.getType() == "Income")
            income += t.getAmount();
        else
            expense += t.getAmount();
    }

    cout << "\nIncome  : " << income << endl;
    cout << "Expense : " << expense << endl;
    cout << "Balance : " << income - expense << endl;
}

void ExpenseTracker::searchTransaction() const {
    string key;
    cout << "Enter keyword: ";
    getline(cin, key);

    bool found = false;
    for (const auto& t : transactions) {
        if (t.getCategory().find(key) != string::npos ||
            t.getDescription().find(key) != string::npos) {
            t.display();
            found = true;
        }
    }

    if (!found)
        cout << "No matching transactions found.\n";
}

void ExpenseTracker::deleteTransaction() {
    if (transactions.empty()) {
        cout << "No transactions available.\n";
        return;
    }

    showAll();

    int index;
    cout << "Enter transaction number to delete: ";
    cin >> index;

    if (index < 1 || index > transactions.size()) {
        cout << "Invalid index!\n";
        return;
    }

    transactions.erase(transactions.begin() + index - 1);
    saveToFile();
    cout << "Transaction deleted.\n";
}

void ExpenseTracker::monthlySummary() const {
    string month, year;
    cout << "Enter month (MM): ";
    cin >> month;
    cout << "Enter year (YYYY): ";
    cin >> year;

    double income = 0, expense = 0;

    for (const auto& t : transactions) {
        string d = t.getDate();
        if (d.substr(3, 2) == month && d.substr(6, 4) == year) {
            if (t.getType() == "Income")
                income += t.getAmount();
            else
                expense += t.getAmount();
        }
    }

    cout << "\nIncome  : " << income << endl;
    cout << "Expense : " << expense << endl;
    cout << "Balance : " << income - expense << endl;
}

void ExpenseTracker::editTransaction() {
    if (transactions.empty()) {
        cout << "No transactions to edit.\n";
        return;
    }

    showAll();

    int index;
    cout << "Enter transaction number: ";
    cin >> index;

    if (index < 1 || index > transactions.size()) {
        cout << "Invalid index!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string category, description;
    double amount;

    cout << "New category: ";
    getline(cin, category);

    cout << "New description: ";
    getline(cin, description);

    cout << "New amount: ";
    cin >> amount;

    Transaction& t = transactions[index - 1];
    t.setCategory(category);
    t.setDescription(description);
    t.setAmount(amount);
    t.updateDate();

    saveToFile();
    cout << "Transaction updated.\n";
}

void ExpenseTracker::exportToCSV() const {
    ofstream file("transactions.csv");

    file << "Date,Type,Category,Description,Amount\n";
    for (const auto& t : transactions) {
        file << t.getDate() << ","
             << t.getType() << ","
             << t.getCategory() << ","
             << t.getDescription() << ","
             << t.getAmount() << "\n";
    }

    file.close();
    cout << "CSV exported successfully.\n";
}

void ExpenseTracker::saveToFile() const {
    ofstream file("data.txt");
    for (const auto& t : transactions) {
        file << t.getType() << "|"
             << t.getCategory() << "|"
             << t.getDescription() << "|"
             << t.getAmount() << "|"
             << t.getDate() << "\n";
    }
}

void ExpenseTracker::loadFromFile() {
    ifstream file("data.txt");
    if (!file) return;

    transactions.clear();
    string line;

    while (getline(file, line)) {
        string type, cat, desc, date;
        double amt;

        stringstream ss(line);
        getline(ss, type, '|');
        getline(ss, cat, '|');
        getline(ss, desc, '|');
        ss >> amt;
        ss.ignore();
        getline(ss, date);

        transactions.push_back(Transaction(type, cat, desc, amt, date));
    }
}
