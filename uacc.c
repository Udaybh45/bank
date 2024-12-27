#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 50

// Global arrays for storing account details
int accountNumbers[MAX_ACCOUNTS];
char accountNames[MAX_ACCOUNTS][MAX_NAME_LENGTH];
float accountBalances[MAX_ACCOUNTS];

// Function prototypes
void createAccount(int *accountCount);
void displayAccounts(int accountCount);
void deposit(int accountCount);
void withdraw(int accountCount);
void saveAccountsToFile(int accountCount);
void loadAccountsFromFile(int *accountCount);

int main() {
    int accountCount = 0;
    int choice;

    // Load accounts from file at the start
    loadAccountsFromFile(&accountCount);

    while (1) {
        printf("\n--- Bank Account Management ---\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (accountCount < MAX_ACCOUNTS) {
                    createAccount(&accountCount);
                } else {
                    printf("Account limit reached!\n");
                }
                break;
            case 2:
                displayAccounts(accountCount);
                break;
            case 3:
                deposit(accountCount);
                break;
            case 4:
                withdraw(accountCount);
                break;
            case 5:
                saveAccountsToFile(accountCount);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to create a new account
void createAccount(int *accountCount) {
    printf("\n--- Create New Account ---\n");
    printf("Enter account number: ");
    scanf("%d", &accountNumbers[*accountCount]);
    printf("Enter account name: ");
    getchar(); 
    fgets(accountNames[*accountCount], MAX_NAME_LENGTH, stdin);
    accountNames[*accountCount][strcspn(accountNames[*accountCount], "\n")] = '\0'; 
    printf("Enter initial balance: ");
    scanf("%f", &accountBalances[*accountCount]);
    (*accountCount)++;
    printf("Account created successfully!\n");
}

// Function to display all accounts
void displayAccounts(int accountCount) {
    if (accountCount == 0) {
        printf("\nNo accounts to display.\n");
        return;
    }

    printf("\n--- List of Accounts ---\n");
    printf("%-15s %-30s %s\n", "Account Number", "Account Name", "Balance");
    for (int i = 0; i < accountCount; i++) {
        printf("%-15d %-30s %.2f\n", accountNumbers[i], accountNames[i], accountBalances[i]);
    }
}

// Function to deposit money
void deposit(int accountCount) {
    int accNumber;
    float amount;
    int found = 0;

    printf("\nEnter account number for deposit: ");
    scanf("%d", &accNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accountNumbers[i] == accNumber) {
            printf("Enter deposit amount: ");
            scanf("%f", &amount);

            if (amount > 0) {
                accountBalances[i] += amount;
                printf("Deposit successful! New balance: %.2f\n", accountBalances[i]);
            } else {
                printf("Invalid deposit amount.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to withdraw money
void withdraw(int accountCount) {
    int accNumber;
    float amount;
    int found = 0;

    printf("\nEnter account number for withdrawal: ");
    scanf("%d", &accNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accountNumbers[i] == accNumber) {
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);

            if (amount > 0 && amount <= accountBalances[i]) {
                accountBalances[i] -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", accountBalances[i]);
            } else if (amount > accountBalances[i]) {
                printf("Insufficient balance!\n");
            } else {
                printf("Invalid withdrawal amount.\n");
           }
           found = 1;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to save accounts to a file (text mode)
void saveAccountsToFile(int accountCount) {
    FILE *file = fopen("uaccounts.txt", "w");
    if (file == NULL) {
        printf("Error saving accounts to file!\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d;%s;%.2f\n", accountNumbers[i], accountNames[i], accountBalances[i]);
    }

    fclose(file);
    printf("Accounts saved successfully!\n");
}

// Function to load accounts from a file (text mode)
void loadAccountsFromFile(int *accountCount) {
    FILE *file = fopen("uaccounts.txt", "r");
    if (file == NULL) {
        printf("No existing account data found. Starting fresh.\n");
        *accountCount = 0;
        return;
    }

    while (fscanf(file, "%d;%49[^;];%f\n", &accountNumbers[*accountCount], accountNames[*accountCount], &accountBalances[*accountCount]) == 3) {
        (*accountCount)++;
    }

    fclose(file);
    printf("Accounts loaded successfully!\n");
}
