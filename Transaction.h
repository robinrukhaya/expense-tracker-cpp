#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
private:
    string type;
    string category;
    string description;
    double amount;
    string date;

public:
    // Constructors
    Transaction(string t, string c, string d, double a);
    Transaction(string t, string c, string d, double a, string dt);

    // Utility
    static string getCurrentDate();

    // Getters
    string getType() const;
    string getCategory() const;
    string getDescription() const;
    double getAmount() const;
    string getDate() const;

    // Setters
    void setCategory(const string& c);
    void setDescription(const string& d);
    void setAmount(double a);
    void setType(const string& t);

    // Other functions
    void updateDate();
    void display() const;
};

#endif
