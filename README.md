# Personal Expense Tracker (C++ OOP)

A **simple, clean, object-oriented personal expense tracker** written in C++ to help you manage income, expenses, and monthly summaries. This project demonstrates **OOP principles** like encapsulation, getters/setters, modular code, and file handling.

---

## 🛠 Features

- Add **Income** and **Expense** transactions
- View all transactions with details
- Calculate **current balance** (Income - Expense)
- Search transactions by **category** or **description**
- Delete and edit existing transactions
- Generate **monthly summary**
- Export transactions to **CSV** for reporting
- **Persistent storage**: transactions saved in `data.txt`

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `with_oop.cpp` | Main program / menu interface |
| `ExpenseTracker.h` | Declaration of `ExpenseTracker` class |
| `ExpenseTracker.cpp` | Definition of `ExpenseTracker` methods |
| `Transaction.h` | Declaration of `Transaction` class |
| `Transaction.cpp` | Definition of `Transaction` methods |
| `.gitignore` | Prevents `.exe` files from being tracked |

---

## 💡 Key Concepts

- **Classes & Objects:** `Transaction` and `ExpenseTracker`  
- **Getters and Setters:** Access and modify private data safely  
- **File Handling:** Read/write transactions from `data.txt`  
- **Vectors:** Store dynamic list of transactions  
- **OOP Principles:** Encapsulation, modularity, clean structure  

---

## ⚡ Usage

1. **Compile:**

```bash
g++ with_oop.cpp ExpenseTracker.cpp Transaction.cpp -o ExpenseTracker
