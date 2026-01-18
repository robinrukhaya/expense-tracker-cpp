#include <iostream>
#include <limits>
#include "ExpenseTracker.h"
#include "Transaction.h"

using namespace std;

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n=== Personal Expense Tracker ===\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. View Transactions\n";
        cout << "4. View Balance\n";
        cout << "5. Search\n";
        cout << "6. Delete\n";
        cout << "7. Monthly Summary\n";
        cout << "8. Edit Transaction\n";
        cout << "9. Export CSV\n";
        cout << "10. Exit\n";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1 || choice == 2) {
            string cat, desc;
            double amt;
            string type = (choice == 1) ? "Expense" : "Income";

            cout << "Category: ";
            cin >> cat;
            cin.ignore();

            cout << "Description: ";
            getline(cin, desc);

            cout << "Amount: ";
            cin >> amt;

            tracker.addTransaction(Transaction(type, cat, desc, amt));
        }
        else if (choice == 3) tracker.showAll();
        else if (choice == 4) tracker.showBalance();
        else if (choice == 5) tracker.searchTransaction();
        else if (choice == 6) tracker.deleteTransaction();
        else if (choice == 7) tracker.monthlySummary();
        else if (choice == 8) tracker.editTransaction();
        else if (choice == 9) tracker.exportToCSV();

    } while (choice != 10);

    return 0;
}
