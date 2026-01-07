#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <limits>
#include <fstream>
#include <sstream>


using namespace std;

class Transaction {
private:
    string type;
    string category;
    string description;
    double amount;
    string date;

public:
    
    Transaction(string t, string c, string d, double a) {
        type = t;
        category = c;
        description = d;
        amount = a;
        date = getCurrentDate();
    }


    Transaction(string t, string c, string d, double a,string dt) {
        type = t;
        category = c;
        description = d;
        amount = a;
        date = dt;
    }

    static string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        char buf[11];
        sprintf(buf, "%02d-%02d-%04d",
                ltm->tm_mday,
                ltm->tm_mon + 1,
                1900 + ltm->tm_year);
        return string(buf);
    }
    string getType() const { return type; }
    string getCategory() const { return category; }
    string getDescription() const { return description; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }

    void display() const {
        cout << date << " | " << type << " | "
             << category << " | " << description
             << " | " << amount << endl;
    }

void setCategory(const string& c) {
    category = c;
}

void setDescription(const string& d) {
    description = d;
}

void setAmount(double a) {
    amount = a;
}

void setType(const string& t) {
    type = t;
}

void updateDate() {
    date = getCurrentDate();
}

};
    

class ExpenseTracker {
private:
    vector<Transaction> transactions;
public:

    ExpenseTracker() {
    loadFromFile();
    }

    void addTransaction(const Transaction& t) {
        transactions.push_back(t);
        saveToFile(); 
    }
    void showAll() const {
        cout << "\n---All Transactions ---\n";
        for(const auto& t : transactions) {
            t.display();
        }
    }
    void searchTransaction() const {
        string keyword;
        cout << "Enter keyword to search: ";
        getline(cin, keyword);

        bool found = false;
        for (const auto& t : transactions) {
            if (t.getCategory().find(keyword) != string::npos ||
                t.getDescription().find(keyword) != string::npos) {
                t.display();
                found = true;
            }
        }

        if (!found)
            cout << "No matching transactions found.\n";
    }


void showBalance() const {
    double totalIncome = 0;
    double totalExpense = 0;

    for (const auto& t : transactions) {
        if (t.getType() == "Income")
            totalIncome += t.getAmount();
        else if (t.getType() == "Expense")
            totalExpense += t.getAmount();
    }

    cout << "\n--- Balance Summary ---\n";
    cout << "Total Income : " << totalIncome << endl;
    cout << "Total Expense: " << totalExpense << endl;
    cout << "Balance      : " << (totalIncome - totalExpense) << endl;
}

void deleteTransaction() {
    if (transactions.empty()) {
        cout << "No transactions to delete.\n";
        return;
    }

    showAll();

    int index;
    cout << "Enter transaction number to delete: ";
    cin >> index;

    if (index < 1 || index > transactions.size()) {
        cout << "Invalid transaction number!\n";
        return;
    }

    transactions.erase(transactions.begin() + (index - 1));
    saveToFile(); 
    cout << "Transaction deleted successfully.\n";
    
}
void saveToFile() const {
    ofstream file("data.txt");
    if (!file) {
        cout << "Error saving file!\n";
        return;
    }

    for (const auto& t : transactions) {
        file << t.getType() << "|"
             << t.getCategory() << "|"
             << t.getDescription() << "|"
             << t.getAmount() << "|"
             << t.getDate()
             << "\n";
    }

    file.close();
}
void loadFromFile() {
    ifstream file("data.txt");
    if (!file) return;

    transactions.clear();
    string line;

    while (getline(file, line)) {
        string type, category, description, date;
        double amount;

        stringstream ss(line);
        getline(ss, type, '|');
        getline(ss, category, '|');
        getline(ss, description, '|');
        ss >> amount;
        ss.ignore();
        getline(ss, date);

        transactions.push_back(
            Transaction(type, category, description, amount, date)
        );
    }

    file.close();
}


void monthlySummary() const {
    string month, year;
    cout << "Enter month (MM): ";
    cin >> month;
    cout << "Enter year (YYYY): ";
    cin >> year;

    double totalIncome = 0;
    double totalExpense = 0;

    for (const auto& t : transactions) {
        string date = t.getDate();

        if (date.substr(3, 2) == month && date.substr(6, 4) == year) {
            if (t.getType() == "Income")
                totalIncome += t.getAmount();
            else if (t.getType() == "Expense")
                totalExpense += t.getAmount();
        }
    }

    cout << "\n--- Monthly Summary (" << month << "-" << year << ") ---\n";
    cout << "Total Income : " << totalIncome << endl;
    cout << "Total Expense: " << totalExpense << endl;
    cout << "Balance      : " << (totalIncome - totalExpense) << endl;
}

void editTransaction() {
    if (transactions.empty()) {
        cout << "No transactions to edit.\n";
        return;
    }

    showAll();

    int index;
    cout << "Enter transaction number to edit: ";
    cin >> index;

    if (index < 1 || index > transactions.size()) {
        cout << "Invalid transaction number!\n";
        return;
    }

    Transaction& t = transactions[index - 1];

    string category, description;
    double amount;
    int typeChoice;

    cout << "Enter new category: ";
    cin >> category;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new description: ";

    getline(cin, description);

    cout << "Enter new amount: ";
    cin >> amount;

    cout << "Change type? (1 = Income, 2 = Expense, 0 = No change): ";
    cin >> typeChoice;
    t.setCategory(category);
    t.setDescription(description);
    t.setAmount(amount);

    if (typeChoice == 1)
        t.setType("Income");
    else if (typeChoice == 2)
        t.setType("Expense");

    t.updateDate();
    saveToFile();

    cout << "Transaction updated successfully.\n";

}

void exportToCSV() const {
    ofstream file("transactions.csv");

    if (!file) {
        cout << "Error creating CSV file!\n";
        return;
    }

    // Header row
    file << "Date,Type,Category,Description,Amount\n";

    for (const auto& t : transactions) {
        file << t.getDate() << ","
             << t.getType() << ","
             << t.getCategory() << ","
             << t.getDescription() << ","
             << t.getAmount() << "\n";
    }

    file.close();
    cout << "Transactions exported to transactions.csv successfully.\n";
}



};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n== Personal Expense Tracker ==\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. View all Transactions\n";
        cout << "4. View Balance\n";
        cout << "5. Search Transactions\n";
        cout << "6. Delete Transaction\n";
        cout << "7. Monthly Summary\n";
        cout << "8. Edit Transaction\n";
        cout << "9. Export to CSV\n";
        cout << "10. Exit\n";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    

        if (choice == 1 || choice == 2) {
            string category, description;
            double amount;
            string type = (choice == 1) ? "Expense" : "Income";

            cout << "Enter Category: ";
            cin >> category;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            cout << "Enter Description: ";
            getline(cin, description);

            cout << "Enter Amount: ";
            cin >> amount;

            tracker.addTransaction(
                Transaction(type, category, description, amount)
            );
        }
        else if (choice == 3) {
            tracker.showAll();
        }
        else if (choice == 4) {
            tracker.showBalance(); 
        }
        else if (choice == 5) {
            tracker.searchTransaction();
        }   
        else if (choice == 6) {
            tracker.deleteTransaction();
        }
        else if (choice == 7) {
            tracker.monthlySummary();
        }
        else if (choice == 8) {
            tracker.editTransaction();
        }
        else if (choice == 9) {
            tracker.exportToCSV();
        }

        else if (choice == 10) {
            cout << "Exiting program...\n";
        }


        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 10);

    return 0;
}

