#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <vector>
#include "Transaction.h"

using namespace std;

class ExpenseTracker {
private:
    vector<Transaction> transactions;

    void saveToFile() const;
    void loadFromFile();

public:
    ExpenseTracker();

    void addTransaction(const Transaction& t);
    void showAll() const;
    void showBalance() const;
    void searchTransaction() const;
    void deleteTransaction();
    void monthlySummary() const;
    void editTransaction();
    void exportToCSV() const;
};

#endif
