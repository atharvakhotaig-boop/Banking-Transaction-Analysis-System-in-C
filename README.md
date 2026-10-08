Banking Transaction Analysis System
A menu-driven C application for managing, searching, sorting, and analyzing banking transactions using Divide and Conquer algorithms.
Features
- Add and manage banking transactions
- Unique Transaction ID validation
- View all transaction records
- Search transactions by Transaction ID
- Customer-specific transaction analysis
- Generate ordered transaction reports
- Find highest and lowest transactions
- Credit/Debit transaction summary
- Automatic sorting algorithm selection
- Binary Search for efficient transaction lookup
- Clean, user-friendly console interface
Algorithms Used
The algorithmic implementation works in the background so users interact with a simple banking-style interface.
- Merge Sort — used for efficient ordering of larger transaction datasets
- Quick Sort — used for smaller datasets
- Binary Search — used for fast Transaction ID lookup
- Recursion — used in the Divide and Conquer implementations
Data Stored
Each transaction contains:
Transaction ID
Customer ID
Date
Transaction Type
Amount

How It Works
1. Add transaction records through the menu.
2. The system validates transaction IDs and transaction details.
3. Transactions can be viewed and analyzed through different options.
4. Sorting is handled automatically by the backend.
5. Transaction searches internally use Binary Search.
6. Reports and summaries provide useful banking insights.
Compilation & Execution
GCC
gcc banking_transaction_analysis.c -o banking

Run:
./banking

Windows
gcc banking_transaction_analysis.c -o banking.exe
banking.exe

Project Structure
Banking-Transaction-Analysis-System/
│
├── banking_transaction_analysis.c
└── README.md

AOA Concepts Demonstrated
This project demonstrates the practical application of:
- Divide and Conquer
- Sorting Algorithms
- Searching Algorithms
- Recursion
- Algorithm Selection
- Data Organization
- Efficient Record Retrieval
Example Menu
============================================================
              BANKING TRANSACTION SYSTEM
============================================================

  1. Add Transaction
  2. View All Transactions
  3. Search Transaction
  4. Transaction Report
  5. Customer Transactions
  6. Transaction Summary
  7. Highest / Lowest Transaction
  0. Exit
============================================================

Technology
Language: C
Domain: Banking / Transaction Analysis
Course: Analysis and Design of Algorithms (AOA)
