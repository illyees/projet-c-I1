#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100
#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    char name[50];
    int clientID;
} Client;

typedef struct {
    int accountID;
    int clientID;
    double balance;
} Account;

typedef struct {
    int transactionID;
    int accountID;
    char type[20];
    double amount;
} Transaction;

Client clients[MAX_CLIENTS];
Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS];

int clientCount = 0;
int accountCount = 0;
int transactionCount = 0;

void createClient(char name[]);
void displayClients();
void createAccount(int clientID, double initialBalance);
void updateAccount(int accountID, double newBalance);
void displayAccountDetails(int accountID);
void displayTransactions(int accountID);
void deleteAccount(int accountID);

int main() {
    createClient("John Doe");
    createClient("Jane Doe");

    displayClients();

    createAccount(0, 1000.0);
    createAccount(1, 500.0);

    displayAccountDetails(0);
    displayAccountDetails(1);

    updateAccount(0, 1500.0);

    displayAccountDetails(0);

    createAccount(0, 2000.0);

    displayTransactions(0);

    deleteAccount(1);

    displayClients();

    return 0;
}

void createClient(char name[]) {
    if (clientCount < MAX_CLIENTS) {
        Client newClient;
        strcpy(newClient.name, name);
        newClient.clientID = clientCount;
        clients[clientCount++] = newClient;
        printf("Client ajoute avec succes.\n");
    } else {
        printf("Le nombre maximum de clients a ete atteint.\n");
    }
}

void displayClients() {
    printf("Liste des clients :\n");
    for (int i = 0; i < clientCount; ++i) {
        printf("%d. %s\n", clients[i].clientID, clients[i].name);
    }
}

void createAccount(int clientID, double initialBalance) {
    if (accountCount < MAX_ACCOUNTS) {
        Account newAccount;
        newAccount.accountID = accountCount;
        newAccount.clientID = clientID;
        newAccount.balance = initialBalance;
        accounts[accountCount++] = newAccount;
        printf("Compte cree avec succes.\n");
    } else {
        printf("Le nombre maximum de comptes a ete atteint.\n");
    }
}

void updateAccount(int accountID, double newBalance) {
    if (accountID >= 0 && accountID < accountCount) {
        accounts[accountID].balance = newBalance;
        printf("Mise a jour du solde du compte %d effectuee avec succes.\n", accountID);
    } else {
        printf("Compte invalide.\n");
    }
}

void displayAccountDetails(int accountID) {
    if (accountID >= 0 && accountID < accountCount) {
        printf("Details du compte %d :\n", accountID);
        printf("Solde : %.2f\n", accounts[accountID].balance);
    } else {
        printf("Compte invalide.\n");
    }
}

void displayTransactions(int accountID) {
    printf("Transactions du compte %d :\n", accountID);
    for (int i = 0; i < transactionCount; ++i) {
        if (transactions[i].accountID == accountID) {
            printf("ID Transaction : %d - Type : %s - Montant : %.2f\n", transactions[i].transactionID, transactions[i].type, transactions[i].amount);
        }
    }
}

void deleteAccount(int accountID) {
    if (accountID >= 0 && accountID < accountCount) {
        for (int i = accountID; i < accountCount - 1; ++i) {
            accounts[i] = accounts[i + 1];
        }
        accountCount--;
        printf("Compte %d supprime avec succes.\n", accountID);
    } else {
        printf("Compte invalide.\n");
    }
}
void performTransaction(int accountID, char type[], double amount) {
    if (accountID >= 0 && accountID < accountCount) {
        if (strcmp(type, "Depot") == 0) {
            accounts[accountID].balance += amount;
        } else if (strcmp(type, "Retrait") == 0) {
            if (accounts[accountID].balance >= amount) {
                accounts[accountID].balance -= amount;
            } else {
                printf("Solde insuffisant pour effectuer le retrait.\n");
                return;
            }
        } else {
            printf("Type de transaction invalide.\n");
            return;
        }

        transactions[transactionCount].transactionID = transactionCount;
        transactions[transactionCount].accountID = accountID;
        strcpy(transactions[transactionCount].type, type);
        transactions[transactionCount].amount = amount;
        transactionCount++;

        printf("Transaction effectuee avec succes.\n");
    } else {
        printf("Compte invalide.\n");
    }
}
