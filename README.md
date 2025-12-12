## 🏦 Bayt AlMal ATM System (C++ Console Application)

### Project Overview

This is a fully functional, console-based **ATM banking simulation** written in modern C++. The application allows an authenticated user to perform secure financial transactions (Withdrawal, Deposit, Check Balance) and manages client data using file persistence.

This project is ideal for developers learning **C++ file I/O**, **robust input validation**, and implementing a reliable transactional system with data synchronization.

---

### 📋 Key System Features

| Feature | Description | Operational Impact |
| :--- | :--- | :--- |
| **Authentication & Access Control** | Client access secured via credential validation (Account Number and PIN Code) against the data vault. | Ensures user identity and prevents unauthorized access to transactions. |
| **Data Integrity Assurance** | **CRITICAL:** Employs a **Synchronous Reload-Modify-Save** workflow to prevent data loss or corruption due to concurrent operations.  | Guarantees the transactional integrity and auditability of the financial ledger. |
| **Withdrawal Compliance** | Transaction rules strictly enforced: amounts must be positive, available in the balance, and compliant with cash denomination standards (multiples of 5). | Maintains balance accuracy and adherence to defined business rules. |
| **Input Stabilization** | Includes extensive input validation, type checking, and buffer management across all user interaction points. | Eliminates program instability and crashes from non-numeric or malformed input. |
| **Real-Time Data Refresh** | Client balance is updated and validated directly from the persistent storage prior to display or transaction execution. | Provides verified, real-time balance information to the user. |
| **Persistence Layer** | Account data is managed via structured, plain-text delimiter-separated file I/O (`fstream`). | Enables durable, persistent, and auditable record keeping. |

---

### 🚀 Getting Started

To compile and run this program, you'll need a C++ compiler (g++ recommended) that supports C++11 or higher.

#### 1. Clone the repository

```bash
git clone [https://github.com/YourUsername/Bayt-AlMal-ATM-System](https://github.com/YourUsername/Bayt-AlMal-ATM-System) # Replace with your repo link
cd Bayt-AlMal-ATM-System
