#include "Transaction.h"
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

Transaction::Transaction(string t, string c, string d, double a) {
    type = t;
    category = c;
    description = d;
    amount = a;
    date = getCurrentDate();
}

Transaction::Transaction(string t, string c, string d, double a, string dt) {
    type = t;
    category = c;
    description = d;
    amount = a;
    date = dt;
}

string Transaction::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buf[11];
    sprintf(buf, "%02d-%02d-%04d",
            ltm->tm_mday,
            ltm->tm_mon + 1,
            1900 + ltm->tm_year);

    return string(buf);
}

string Transaction::getType() const {
    return type;
}

string Transaction::getCategory() const {
    return category;
}

string Transaction::getDescription() const {
    return description;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getDate() const {
    return date;
}

void Transaction::setCategory(const string& c) {
    category = c;
}

void Transaction::setDescription(const string& d) {
    description = d;
}

void Transaction::setAmount(double a) {
    amount = a;
}

void Transaction::setType(const string& t) {
    type = t;
}

void Transaction::updateDate() {
    date = getCurrentDate();
}

void Transaction::display() const {
    cout << date << " | "
         << type << " | "
         << category << " | "
         << description << " | "
         << amount << endl;
}
