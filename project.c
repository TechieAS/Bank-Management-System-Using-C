#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_PASSWORD "admin123"
#define IFSC_code "BANK1234567"
#define MAX_ACCOUNTS 100

void depositMoney(int index);
void withdrawmoney(int index);
void balance(int index);
void adminLogin();
void viewAllAccounts();
void searchAccount();
void viewTotalBankBalance();
void exportDataToCSV();

struct Account
{
    int account_number;
    char holder_name[20];
    char password[10];
    char addhar[13]; 
    float balance;
    char ifsc[12];
};

int account_count = 0;
struct Account accounts[MAX_ACCOUNTS];

void encryptPassword(char *password)
{
    for (int i = 0; password[i] != '\0'; i++)
    {
        password[i] += 2;
    }
}

void saveData()
{
    FILE *file = fopen("bank_data.bin", "wb");
    if (file == NULL)
    {
        printf("Error: Could not save data.\n");
        return;
    }
    fwrite(&account_count, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), account_count, file);
    fclose(file);
}

void loadData()
{
    FILE *file = fopen("bank_data.bin", "rb");
    if (file == NULL)
    {
        return;
    }
    fread(&account_count, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), account_count, file);
    fclose(file);
}

void createAccount()
{
    if (account_count >= MAX_ACCOUNTS)
    {
        printf("Bank database is full! Cannot create new account.\n");
        return;
    }

    struct Account newAccount;
    newAccount.account_number = 1000 + account_count;
    strcpy(newAccount.ifsc, IFSC_code);

    printf("Enter name: ");
    scanf("%19s", newAccount.holder_name);

    printf("Enter 12-digit Aadhar number: ");
    scanf("%12s", newAccount.addhar);
    if (strlen(newAccount.addhar) != 12)
    {
        printf("Invalid Aadhar number. Must be 12 digits.\n");
        return;
    }

    printf("Set password (max 9 characters): ");
    scanf("%9s", newAccount.password);
    encryptPassword(newAccount.password);

    newAccount.balance = 0.0;
    accounts[account_count++] = newAccount;

    printf("\nAccount created successfully! Your Account Number is: %d\n", newAccount.account_number);
    saveData();
}

void userLogin()
{
    int accountNumber;
    char inputPassword[50];
    int choice2;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    encryptPassword(inputPassword);

    int userIndex = -1;
    for (int i = 0; i < account_count; i++)
    {
        if (accounts[i].account_number == accountNumber &&
            strcmp(accounts[i].password, inputPassword) == 0)
        {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1)
    {
        printf("Login failed: Invalid account number or password.\n");
        return;
    }

    printf("\nLogin successful! Welcome, %s.\n", accounts[userIndex].holder_name);

    do
    {
        printf("\n----- Account Menu -----\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. View Balance\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);

        switch (choice2)
        {
        case 1:
            depositMoney(userIndex);
            break;
        case 2:
            withdrawmoney(userIndex);
            break;
        case 3:
            balance(userIndex);
            break;
        case 4:
            printf("Logged out successfully.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice2 != 4);
}

void depositMoney(int index)
{
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0)
    {
        printf("Invalid amount. Deposit must be positive.\n");
        return;
    }
    accounts[index].balance += amount;
    saveData();
    printf("Amount deposited successfully. Current balance: %.2f\n", accounts[index].balance);
}

void withdrawmoney(int index)
{
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0)
    {
        printf("Invalid amount. Withdrawal must be positive.\n");
        return;
    }
    if (amount > accounts[index].balance)
    {
        printf("Withdrawal failed. Insufficient funds.\n");
        return;
    }

    accounts[index].balance -= amount;
    saveData();
    printf("Amount withdrawn successfully. Current balance: %.2f\n", accounts[index].balance);
}

void balance(int index)
{
    printf("Your current balance is: %.2f\n", accounts[index].balance);
}

void adminLogin()
{
    char inputPassword[50];
    int choice3;

    printf("Enter admin password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputPassword, ADMIN_PASSWORD) != 0)
    {
        printf("Invalid admin password!\n");
        return;
    }

    printf("\nAdmin login successful!\n");
    do
    {

        printf("\n------- Admin Menu -------\n");
        printf("1. View total bank balance\n");
        printf("2. View all accounts\n");
        printf("3. Search for an account\n");
        printf("4. Export data to CSV file\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice3);

        switch (choice3)
        {
        case 1:
            viewTotalBankBalance();
            break;
        case 2:
            viewAllAccounts();
            break;
        case 3:
            searchAccount();
            break;
        case 4:
            exportDataToCSV();
            break;
        case 5:
            printf("Admin logged out.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice3 != 5);
}

void viewTotalBankBalance()
{
    float totalBalance = 0.0;
    for (int i = 0; i < account_count; i++)
    {
        totalBalance += accounts[i].balance;
    }
    printf("\nTotal balance across all accounts in the bank: %.2f INR\n", totalBalance);
}

void viewAllAccounts() {
    if (account_count == 0) {
        printf("No accounts in the system.\n");
        return;
    }

    printf("\n--- All Bank Accounts ---\n");
    printf("------------------------------------------------------------------\n");
    printf("%-10s | %-20s | %-12s | %s\n", "Acc No.", "Holder Name", "Aadhar", "Balance (INR)");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < account_count; i++) {
        printf("%-10d | %-20s | %-12s | %.2f\n",
               accounts[i].account_number,
               accounts[i].holder_name,
               accounts[i].addhar,
               accounts[i].balance);
    }
    printf("------------------------------------------------------------------\n");
}

void searchAccount() {
    int accountNumber;
    printf("Enter account number to search: ");
    scanf("%d", &accountNumber);

    int foundIndex = -1;
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_number == accountNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("\n--- Account Found ---\n");
        printf("Account Number: %d\n", accounts[foundIndex].account_number);
        printf("Holder Name   : %s\n", accounts[foundIndex].holder_name);
        printf("Aadhar Number : %s\n", accounts[foundIndex].addhar);
        printf("Balance       : %.2f\n", accounts[foundIndex].balance);
        printf("IFSC Code     : %s\n", accounts[foundIndex].ifsc);
        printf("-----------------------\n");
    } else {
        printf("Account with number %d not found.\n", accountNumber);
    }
}

void exportDataToCSV() {
    FILE *file = fopen("bank_data_export.csv", "w");
    if (file == NULL) {
        printf("Error creating CSV file.\n");
        return;
    }
    fprintf(file, "AccountNumber,HolderName,AadharNumber,Balance,IFSC\n");
    for (int i = 0; i < account_count; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%s\n",
                accounts[i].account_number,
                accounts[i].holder_name,
                accounts[i].addhar,
                accounts[i].balance,
                accounts[i].ifsc);
    }
    fclose(file);
    printf("Data exported to bank_data_export.csv successfully.\n");
}


int main()
{
    int choice;
    loadData();

    do
    {
        printf("\n=== BANK MANAGEMENT SYSTEM ===\n");
        printf("1. Create a new account\n");
        printf("2. Login to your account\n");
        printf("3. Admin login\n"); 
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            userLogin();
            break;
        case 3:
            adminLogin(); 
            break;
        case 4:
            printf("Thank you for using the bank system. Exiting.\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }

    } while (choice != 4);

    return 0;
}