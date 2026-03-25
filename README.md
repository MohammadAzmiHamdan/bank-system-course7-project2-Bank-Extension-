# bank-system-course7-project2-Bank-Extension-
This project is an extension of my previous (Bank ) System, developed as Project 2 in Algorithms &amp; Problem Solving Level 3, which is the 7th course in the roadmap of Mohammad Abu-Hadhoud.
# Bank Management System – Course 7 Project 2 Extension (C++)
(Bank Extinsion Project 2 )
## Overview

This project is an extension of my previous **Client Management System**, developed as **Project 2 in Algorithms & Problem Solving Level 3**, which is the **7th course in the roadmap of Mohammad Abu-Hadhoud**.

The goal of this extension was to move from basic client management into transaction processing, simulating a small banking system using file-based persistent storage.

The project focuses on strengthening problem solving skills through building complete functional systems using C++.

---

## What was added in this extension

Compared to the first version, this project introduces a full **Transactions Module**, including:

* Deposit money into client accounts
* Withdraw money with balance validation
* Display total balances of all clients
* Dedicated transactions menu
* Immediate balance persistence to file after every transaction

---

## Core Features

### Client Management

* Show all clients list
* Add new client
* Prevent duplicate account numbers
* Delete client
* Update client information
* Find client by account number

### Transactions Management

* Deposit operation
* Withdraw operation
* Prevent withdrawing beyond available balance
* Show updated balance after each transaction
* Calculate total balances of all clients

---

## Client Record Format

Each client record is stored in text file using this structure:

```txt id="f0h3l7"
AccountNumber#//#PinCode#//#ClientName#//#Phone#//#Balance
```

Example:

```txt id="8w4w9f"
12344#//#3333#//#Mohammad Azmi Mohammad Hamdan#//#0788592929#//#5000.000000
```

---

## Programming Concepts Practiced

This project helped me practice:

* File Handling (`fstream`)
* String Parsing and Splitting
* Structs
* Vectors
* CRUD Operations
* Search Algorithms
* Input Validation
* Transactions Logic
* Balance Processing
* Function Decomposition
* Console-Based Menu Design

---

## Main Modules

### File Processing

* Load client data from file
* Save updated records back to file

### Client Processing

* Search by account number
* Modify records
* Delete safely

### Transactions Processing

* Deposit balance
* Withdraw balance
* Validate available funds
* Update balances immediately

---

## System Menus

### Main Menu

* Clients List
* Add Client
* Delete Client
* Update Client
* Find Client
* Transactions
* Exit

### Transactions Menu

* Deposit
* Withdraw
* Total Balances
* Return to Main Menu

---

## Learning Outcome

This extension improved my ability to:

* Expand an existing system without rewriting it
* Add new modules cleanly
* Handle banking logic step by step
* Connect file storage with transaction operations

---

## Future Improvements

* Input type validation
* Better menu loop architecture
* Login system
* Separate files for modules
* Object-Oriented refactoring

---

## Author

Mohammad Hamdan

---

## Course Reference

Algorithms & Problem Solving Level 3
Course 7 – Project 2 Extension
