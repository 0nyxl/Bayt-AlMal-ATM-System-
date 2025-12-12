## 🏦 Bayt AlMal ATM System (C++ Console Application)

### Project Overview

This is a fully functional, console-based **ATM banking simulation** written in modern C++. The application allows an authenticated user to perform secure financial transactions (Withdrawal, Deposit, Check Balance) and manages client data using file persistence.

This project is ideal for developers learning **C++ file I/O**, **robust input validation**, and implementing a reliable transactional system with data synchronization.

---

### 📋 Features

| Feature | Description | Status |
| :--- | :--- | :--- |
| **Secure Authentication** | Login using Account Number and PIN Code. | Complete |
| **Transaction Integrity** | **Critical:** Implements a **reload-then-save** mechanism to guarantee the data file is never corrupted by stale data. | Hardened |
| **Withdrawal Options** | Includes **Quick Withdraw** (predefined amounts) and **Normal Withdraw** (custom amounts). | Complete |
| **Deposit Funds** | Allows positive whole dollar deposits. | Complete |
| **Real-Time Balance** | Retrieves the absolute latest balance directly from the data file for the current session. | Complete |
| **Input Robustness** | Comprehensive error checking against non-numeric, negative, or invalid transaction amounts (e.g., non-multiples of 5). | Hardened |
| **Data Storage** | Stores all client records in a structured text file (e.g., `Gringotts_Vaults.txt`). | Complete |

---

### 🚀 Getting Started

To compile and run this program, you'll need a C++ compiler (g++ recommended) that supports C++11 or higher.

#### 1. Clone the repository

```bash
git clone [https://github.com/YourUsername/Bayt-AlMal-ATM-System](https://github.com/YourUsername/Bayt-AlMal-ATM-System) # Replace with your repo link
cd Bayt-AlMal-ATM-System
