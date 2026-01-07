#include <iostream>   // for input/output
#include <vector>     // to storemlist of transaction
#include <string>     // to handle text like category
#include <limits>     // for numaric_limit
#include <fstream>    // for file I/O
#include <sstream>    //for stringstream
#include <ctime>      // for getting current date

using namespace std;

//structure to store one transaction
struct Transaction {
    string type;        //"income or expense"
    string category;    // example "food,salery"
    string description; // short note about about transaction
    double amount;      // money involved
    string date;        // New field for storing date
};


// function to save all transactions to file
void saveToFile(const vector<Transaction>& transactions) {
    ofstream file("data.txt");
    if (!file){
        cout << " Error saving to file!\n";
        return;
    }
    for (auto &t : transactions) {
        file << t.date<< "|" << t.type << "|" << t.category << "|" << t.description << "|" <<t.amount << "\n";
    }
    file.close();
}

// Function to load transactions from file
void loadFromFile(vector<Transaction>& transactions) {
    ifstream file("data.txt");
    if (!file) {
        return; //No file found, start fresh
    }
    transactions.clear();
    string line;
    while (getline(file,line)) {
        Transaction t;
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|",pos1 +1);
        size_t pos3 = line.find("|", pos2 +1);
        size_t pos4 = line.find("|", pos3 +1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) continue;

        t.date = line.substr(0,pos1);
        t.type = line.substr(pos1 + 1, pos2 - pos1 - 1);
        t.category = line.substr(pos2 +1, pos3-pos2-1);
        t.description = line.substr(pos3 + 1, pos4- pos3-1);
        t.amount = stod(line.substr(pos4+1));

        transactions.push_back(t);
    }
    file.close();
}

//Function to calculate and display balance

void calculateBalance(const vector<Transaction>& transactions) {
    double totalIncome = 0, totalExpense = 0;
    for ( auto &t: transactions) {
        if (t.type == "Income") totalIncome += t.amount;
        else if (t.type == "Expense") totalExpense += t.amount;
    }
    cout <<"\n--- Balance Sumary ---\n";
    cout << "Total Income : " << totalIncome << "\n";
    cout << "Total Expense: " << totalExpense<<"\n";
    cout << "Balance      : " << (totalIncome - totalExpense) << "\n";
}

//Function to  get current date
string getCurrentDate() {
    time_t now = time(0);
    tm*ltm = localtime(&now);
    char dateStr[11];
    sprintf(dateStr, "%02d-%02d-%04d",
            ltm->tm_mday,
            ltm->tm_mon +1,
            1900 + ltm->tm_year);
    return string(dateStr);
}

// search transaction by Keyword ( category ) 
void searchTransactions(const vector<Transaction>& transactions) {
    cout<< " Enter Keyword to search: ";
    string keyword;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,keyword);

    cout << "\n--- Search Results ---\n";
    bool found = false;
    for ( int i = 0;  i < transactions.size(); i++ ) {
        if (transactions[i].category.find(keyword) != string::npos ||
            transactions[i].description.find(keyword) != string::npos) {
            cout << i +1 << "." << transactions[i].date << "|"
                 << transactions[i].type << "|"
                 << transactions[i].category << "|"
                 << transactions[i].description << "|" 
                 << transactions[i].amount << "\n";
            found = true;
        }
    }
    if (!found) cout << " no matchig transactions found . \n";
}

// delete transactions by index
void deleteTransaction(vector<Transaction>& transactions) {
    cout << " Enter transactoin number to delet: " ;
    int index;
    cin >> index;
    if ( index < 1 || index > transactions.size()) {
        cout << " Invalid transaction number!\n";
        return;
    }
    transactions.erase(transactions.begin() + ( index - 1));
    saveToFile(transactions);
    cout << " Transaction delete succesfully.\n";
}

// edit transaction by index
void editTransaction(vector<Transaction>& transactions) {
    cout << " Enter transaction number to edit:";
    int index;
    cin >> index;
    if ( index < 1 || index > transactions.size()) {
        cout << " Invalidtransaction numebr!\n";
        return;

    }
    Transaction &t = transactions[index-1];

    cout << "\nEditing Transaction: " << t.date << "|" << t.type << "|"
         << t.category <<"|" << t.description << "|" << t.amount << "\n";
         
    cout << "Enter new category ( current : " << t.category << "): ";
    cin >> t.category;
    cout <<" Enter new description (current : " << t.description << "):";
    cin.ignore();
    getline(cin, t.description);
    cout << " Enter new amount(current:" << t.amount << "):";
    cin >> t.amount;

    cout << "Do you want to change type? ( 1 = Income, 2 =  'Expense, 0=No change):";
    int typeChoice;
    cin >> typeChoice;
    if ( typeChoice == 1) t.type = " Income";
    else if (typeChoice == 2) t.type = "Expense";

    t.date = getCurrentDate(); // update date to today

    saveToFile(transactions);
    cout << " Transaction update succcesfully.\n";

}

// monthly summery
void monthlySummary(const vector<Transaction>& transactions) {
    cout << " Enter month (MM) and year (YYYY):";
    string month, year;
    cin >> month >> year;

    double totalIncome = 0, totalExpense = 0;
    for (auto &t : transactions) {
        if ( t.date.substr(3,2) == month && t.date.substr(6,4) == year) {
            if (t.type == "Income") totalIncome += t.amount;
            else if (t.type == "Expense") totalExpense += t.amount;
        }
    }
    cout << "\n--- Monthly Summary (" << month << "-" << year << ") ---\n";
    cout << " Total Income : "<< totalIncome << "\n";
    cout << " Total Expense: "<< totalExpense << "\n";
    cout << "Balance       : "<< (totalIncome - totalExpense) << "\n";
}

//Export transaction to csv file
void exportToCsv(const vector<Transaction>& transactions) {
    ofstream file("transactions.csv");
    if(!file.is_open()) {
        cout << " Enter creating cse file!|n";
        return;
    }

    // Write header row
    file << "Date,Type,Category<Description,Amount\n";


    //Write all transaction
    for (const auto &t : transactions) {
        file << t.date <<","
             << t.type <<","
             << t.category << ","
             << "\"" << t.description<< "\""<<","  // quotes protect comma in description
             << t.amount << "\n";
    }

    file.close();
    cout <<"Transactions exported succesfully to transactions.csv\n";
}

// main program
int main () {
    vector<Transaction> transactions; //list od all transaction
    int choice = 0;

    //load existing transaction
    loadFromFile(transactions);

    while (choice != 10) {  //infinite loop until user exits
        //menu
        cout << "\n== Personal Expense Tracker ==\n";
        cout << "1. Add Expense\n";
        cout << "2. Add Income\n";
        cout << "3. view all Transactions\n";
        cout << "4. View Balance\n";
        cout << "5. Search Transactions\n";
        cout << "6. Delete Transaction\n";
        cout << "7. Monthly Summary\n";
        cout << "8. Edit Transaction\n";
        cout << "9. Export to csv\n";
        cout << "10. Exit\n";
        cout << "   Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }


        if (choice ==1) { // Add Expense
            Transaction t;
            t.type = "Expense";
            cout << "Enter Category:";
            cin >> t.category ;
            cout << "Enter Description: ";
            cin.ignore(); // To avoid skipping getline after cin
            getline(cin, t.description);
            cout << "Enter Amount: ";
            cin >> t.amount;
            t.date = getCurrentDate();
            transactions.push_back(t); // Add to list
            saveToFile(transactions);
        }

        else if (choice ==2) { // add Income
            Transaction t;
            t.type = "Income";
            cout << "Enter Category: ";
            cin >>t.category;
            cout << "Enter Description: ";
            cin.ignore();
            getline(cin, t.description);
            cout << "Enter Amount: ";
            cin >>t.amount;
            t.date = getCurrentDate(); //store current date
            transactions.push_back(t);
            saveToFile(transactions);
        }

        else if(choice == 3) { // view transactions
            cout << "\n--- All Transactions ---\n";
            for (int i = 0; i < transactions.size(); i++) {
                cout<< i+1 << ". "
                    << transactions[i].date<< "|"
                    << transactions[i].type<<" |"
                    << transactions[i].category << "|"
                    << transactions[i].description << "|"
                    << transactions[i].amount <<"\n";       
            }
        }

        else if (choice == 4) { //view balance
            calculateBalance(transactions);
        }

        else if (choice == 5) { //search Transactions
            searchTransactions(transactions);
        }

        else if ( choice == 6) {  // Delete Transaction
            deleteTransaction(transactions);
        }

        else if (choice == 7) {  // Monthly Summary
            monthlySummary(transactions);
        }

        else if ( choice ==8) {  // edit transaction
            editTransaction(transactions);
        }

        else if ( choice == 9) {
            exportToCsv(transactions);
        }

        else if ( choice == 10) {
            cout << " Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid choice! TRY again.\n";
        }
    }

    return 0;
}
