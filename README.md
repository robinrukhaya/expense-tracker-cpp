# 💰 Personal Expense Tracker — C++ OOP

<p align="left">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img src="https://img.shields.io/badge/Paradigm-OOP-7c6fff?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Storage-File%20Handling-00e5a0?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge"/>
</p>

> A clean, object-oriented CLI application to track your income and expenses — built entirely in C++ using core OOP principles.

---

## 🎯 What This Project Does

Managing money is a real-world problem. This project solves it with a **terminal-based expense tracker** that lets you add transactions, check your balance, search by category, and export reports — all without touching a database or framework. Just pure C++.

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| ➕ Add Transactions | Log income or expense with amount, category & description |
| 📋 View All | Display all transactions with full details |
| 💵 Balance Check | Instantly calculate Income − Expenses |
| 🔍 Search | Filter transactions by category or description |
| ✏️ Edit & Delete | Modify or remove any existing transaction |
| 📅 Monthly Summary | View a breakdown of spending by month |
| 📤 CSV Export | Export all data to `transactions.csv` for Excel/Sheets |
| 💾 Persistent Storage | All data saved to `data.txt` — survives program restarts |

---

## 📁 Project Structure

```
expense-tracker-cpp/
│
├── with_oop.cpp          # Main program — menu & user interface
├── ExpenseTracker.h      # ExpenseTracker class declaration
├── ExpenseTracker.cpp    # ExpenseTracker class methods
├── Transaction.h         # Transaction class declaration
├── Transaction.cpp       # Transaction class methods
├── data.txt              # Persistent storage file (auto-created)
├── transactions.csv      # Exported CSV report
└── .gitignore            # Ignores compiled .exe files
```

---

## 💡 OOP Concepts Demonstrated

This project was built to practice and showcase real Object-Oriented Programming:

- **Encapsulation** — Private data members accessed via getters/setters
- **Classes & Objects** — `Transaction` and `ExpenseTracker` as separate classes
- **Modularity** — Logic split across `.h` header and `.cpp` implementation files
- **File Handling** — Read/write persistence using `fstream`
- **Vectors (STL)** — Dynamic list management with `std::vector<Transaction>`

---

## ⚡ How to Run

### Prerequisites
- A C++ compiler (g++ recommended)
- Terminal / Command Prompt

### Steps

```bash
# 1. Clone the repository
git clone https://github.com/robinrukhaya/expense-tracker-cpp.git

# 2. Navigate into the folder
cd expense-tracker-cpp

# 3. Compile all files
g++ with_oop.cpp ExpenseTracker.cpp Transaction.cpp -o ExpenseTracker

# 4. Run the program
./ExpenseTracker        # Linux/Mac
ExpenseTracker.exe      # Windows
```

---

## 🖥️ Sample Menu

```
===== Personal Expense Tracker =====
1. Add Transaction
2. View All Transactions
3. Check Balance
4. Search by Category
5. Edit Transaction
6. Delete Transaction
7. Monthly Summary
8. Export to CSV
9. Exit
=====================================
Enter your choice:
```

---

## 🧠 What I Learned

- Structuring a multi-file C++ project with header files
- Implementing OOP from scratch without frameworks
- File I/O for persistent data storage
- Using STL vectors to manage dynamic data
- Building a clean, user-friendly CLI interface

---

## 🔮 Future Improvements

- [ ] Add date filtering for transactions
- [ ] Add budget limit alerts
- [ ] Build a GUI version using Qt
- [ ] Add password protection for privacy

---

## 👨‍💻 Author

**Robin Rukhaya**
B.Tech CSE | IILM University | Aspiring SDE

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-0077B5?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/robin-rukhaya-124a70348)
[![GitHub](https://img.shields.io/badge/GitHub-Follow-100000?style=flat-square&logo=github)](https://github.com/robinrukhaya)
[![LeetCode](https://img.shields.io/badge/LeetCode-Profile-FFA116?style=flat-square&logo=leetcode&logoColor=black)](https://leetcode.com/u/RobinRukhaya/)

---

> *"First, solve the problem. Then, write the code."*
