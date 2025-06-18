<p align="center">
  <pre>
  _   _   _   _   _   _   _
 / \ / \ / \ / \ / \ / \ / \
( B | A | N | K | - | C | L | I )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/
  </pre>
</p>

<h1 align="center">Bank Management System in C</h1>

<p align="center">
  A robust and feature-rich command-line banking application built entirely in C.
</p>

<p align="center">
  <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License"></a>
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/Platform-Console-lightgrey.svg" alt="Platform">
  <img src="https://img.shields.io/badge/Status-Complete-brightgreen.svg" alt="Status">
</p>

This project is a comprehensive console-based simulation of a banking system. It provides essential banking functionalities for both standard users and administrators, focusing on data persistence, modular design, and a clear user interface. It serves as an excellent example of fundamental C programming concepts applied to a practical, real-world scenario.

---

### 📋 Table of Contents

- [Live Demo](#-live-demo)
- [✨ Key Features](#-key-features)
- [🧠 Core Concepts Demonstrated](#-core-concepts-demonstrated)
- [🛠️ Technical Deep-Dive](#️-technical-deep-dive)
- [🚀 How to Compile and Run](#-how-to-compile-and-run)
- [🤝 Contributing](#-contributing)
- [📜 License](#-license)

---

## 🎥 Live Demo

A quick walkthrough of creating an account, logging in, and performing a transaction.

*(**Pro-tip:** You can create a GIF like this for your own repository using tools like [asciinema](https://asciinema.org/) and `gif-by-cli` or a screen recorder like Peek or Kap.)*

![Demo GIF Placeholder](https://user-images.githubusercontent.com/10931291/159239018-362241f8-3e3c-4a9c-9396-a0a4c2645672.gif)
*(This is a placeholder GIF. Replace it with a recording of your application in action!)*

---

## ✨ Key Features

### 👤 For Users
-   🔐 **Secure Account Creation**: Onboard new users with a unique account number, name, Aadhar, and a password.
-   🔑 **User Authentication**: Safe login system using account number and password.
-   💵 **Deposit & Withdraw**: Perform basic transactions with real-time balance updates.
-   📊 **Balance Inquiry**: Check account balance instantly.
-   🚪 **Logout**: Securely end the user session.

### 👑 For Administrators
-   🛡️ **Admin Panel**: A separate, password-protected portal for bank management.
-   💰 **View Total Bank Capital**: Get a consolidated view of the total balance across all accounts.
-   📋 **List All Accounts**: Display a neatly formatted table of all registered accounts and their details.
-   🔍 **Search for Specific Account**: Quickly find and view details of any account using its number.
-   📄 **Export to CSV**: Export all account data to a `bank_data_export.csv` file for reporting or analysis in other tools.

---

## 🧠 Core Concepts Demonstrated

This project is a practical application of the following C programming concepts:

-   **Data Structures**: Using `struct` to model real-world entities (an `Account`).
-   **File I/O**: Reading from and writing to binary files (`fopen`, `fread`, `fwrite`, `fclose`) for persistent data storage.
-   **Arrays & Pointers**: Managing a collection of accounts using an array of structs.
-   **String Manipulation**: Using functions from `<string.h>` for handling names, passwords, and other text data.
-   **Modular Programming**: Breaking down the application into logical, reusable functions (e.g., `createAccount`, `userLogin`, `depositMoney`).
-   **Conditional Logic**: Extensive use of `if-else` and `switch-case` for menu-driven navigation and data validation.
-   **Loops**: Using `for` and `do-while` loops for iterating over data and controlling program flow.

---

## 🛠️ Technical Deep-Dive

<details>
<summary><strong>Click to expand for technical details</strong></summary>

### Program Flow
The application operates on a primary `do-while` loop in the `main` function, presenting the main menu. Based on the user's choice, it delegates tasks to specific functions. The system is designed with two distinct user roles: the standard customer and the administrator, each with their own sub-menu and set of privileges.

### Data Storage
-   **`bank_data.bin`**: This is the core database of the application. It's a binary file that stores the `account_count` integer, followed by the array of `Account` structs.
    -   **Why binary?** Binary files are more compact and faster to read/write for structured data compared to text files. They also prevent casual tampering with the data.
-   **`bank_data_export.csv`**: This file is generated on-demand by the administrator. It's a Comma-Separated Values file, ideal for importing into spreadsheet software like Excel or Google Sheets for analysis and reporting.

### Password Handling - A Note on Security
The `encryptPassword` function uses a simple **Caesar cipher** (shifting each character's ASCII value by 2).

> **⚠️ IMPORTANT:** This method is for educational demonstration only and is **NOT SECURE**. It is trivially reversible and should never be used in a production environment. Real-world applications must use strong, one-way hashing algorithms (like **Argon2**, **bcrypt**, or **scrypt**) with salts to store passwords securely.

</details>

---

## 🚀 How to Compile and Run

<details>
<summary><strong>Click for step-by-step instructions</strong></summary>

### Prerequisites
-   A C compiler, such as **GCC** (GNU Compiler Collection).
    -   **Linux/macOS**: Usually pre-installed. Verify with `gcc --version`.
    -   **Windows**: Install a development environment like [MinGW-w64](https://www.mingw-w64.org/) or use the Windows Subsystem for Linux (WSL).

### Steps
1.  **Clone or Download:**
    ```sh
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```
    Or simply download the `bank_system.c` file.

2.  **Compile:**
    Open your terminal and run the GCC command:
    ```sh
    gcc bank_system.c -o bank_system
    ```
    This command compiles the source code and creates an executable file named `bank_system` (or `bank_system.exe` on Windows).

3.  **Run:**
    Execute the compiled program from your terminal:
    ```sh
    ./bank_system
    ```

### Default Admin Credentials
-   **Password**: `admin123`

### ⚠️ Troubleshooting Common C Input Issues
The program uses `scanf` for input, which can sometimes leave a newline character (`\n`) in the input buffer, causing subsequent `scanf` calls to misbehave. If you experience unexpected behavior (e.g., menus skipping), you may need to clear the input buffer. A common way to do this is to add a small utility function:

```c
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
