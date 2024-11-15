#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "History.c"
#include "users.c"
#include "product.c"
#include "rengine.c"

#define MAX_SIZE 1000

void displayProducts(NODE *productHashTable) {
    printf("\nAvailable Products:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (productHashTable[i].flag == 1) {
            printf("PID: %d, Name: %s, Category: %s, Inventory: %d\n",
                   productHashTable[i].PID, productHashTable[i].name,
                   productHashTable[i].category, productHashTable[i].inventory);
        }
    }
}

void displayBrowsingHistory(int userID, User *ht) {
    User *user = search(userID, ht);
    if (user != NULL) {
        printf("Browsing History for UserID: %d, Name: %s\n", user->userID, user->name);
        printf("Browsed Products: ");
        for (int i = 0; i < user->browsedCount; i++) {
            printf("%d ", user->browsedProducts[i]);
        }
        printf("\n");
    } else {
        printf("User not found.\n");
    }
}
void displayPurchaseHistory(int userID, User *ht) {
    User *user = search(userID, ht);
    if (user != NULL) {
        printf("Purchase History for UserID: %d, Name: %s\n", user->userID, user->name);
        printf("Purchased Products: ");
        for (int i = 0; i < user->purchasedCount; i++) {
            printf("%d ", user->purchasedProducts[i]);
        }
        printf("\n");
    } else {
        printf("User not found.\n");
    }
}



int main() {
    SplayTree *browsingHistory = (SplayTree *)malloc(sizeof(SplayTree));
    browsingHistory->root = NULL;

    SplayTree *purchaseHistory = (SplayTree *)malloc(sizeof(SplayTree));
    purchaseHistory->root = NULL;

    User *usersHashTable = (User *)malloc(sizeof(User) * MAX_SIZE);
    init_hashtable(usersHashTable);

    NODE *productHashTable = (NODE *)malloc(sizeof(NODE) * MAX_SIZE);
    initialize_hashTable(productHashTable);

    int numUsers = MAX_SIZE;
    Graph *userGraph = createGraph(numUsers, usersHashTable);
    buildGraph(userGraph);

    addProduct(101, "Laptop", "Electronics", 50, productHashTable);
    addProduct(102, "Smartphone", "Electronics", 100, productHashTable);
    addProduct(103, "Headphones", "Accessories", 200, productHashTable);
    addProduct(104, "Mouse", "Accessories", 300, productHashTable);
    addProduct(105, "Keyboard", "Accessories", 400, productHashTable);
    addProduct(106, "Monitor", "Accessories", 500, productHashTable);
    addProduct(107, "wires", "Accessories", 600, productHashTable);
    addProduct(108, "Mousepad", "Accessories", 700, productHashTable);
    addProduct(109, "Tablet", "Electronics", 800, productHashTable);

    int userID;
    User *currentUser = NULL;

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Create New User\n");
        printf("2. Switch User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        int mainChoice;
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: {
                printf("Enter UserID: ");
                scanf("%d", &userID);
                char name[100], email[100];
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Email: ");
                scanf("%s", email);
                addUser(userID, name, email, usersHashTable);
                currentUser = search(userID, usersHashTable);
                printf("User created and logged in as UserID: %d\n", currentUser->userID);
                break;
            }
           case 2: {
                printf("Enter UserID to switch to: ");
                scanf("%d", &userID);
                currentUser = search(userID, usersHashTable);
                if (currentUser) {
                    printf("Switched to UserID: %d\n", currentUser->userID);
                } else {
                    printf("User not found. Please create the user first.\n");
                }
                break;
            }

            case 3: {
                free(browsingHistory);
                free(purchaseHistory);
                free(usersHashTable);
                free(productHashTable);
                for (int i = 0; i < userGraph->numUsers; i++) {
                    free(userGraph->adjMatrix[i]);
                }
                free(userGraph->adjMatrix);
                free(userGraph);
                exit(0);
            }

            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (currentUser != NULL) {
            while (1) {
                printf("\n--- User Menu (UserID: %d) ---\n", currentUser->userID);
                printf("1. Browse Products\n");
                printf("2. Purchase Product\n");
                printf("3. View Browsing History\n");
                printf("4. View Purchase History\n");
                printf("5. Get Recommendations\n");
                printf("6. Log Out\n");
                printf("Enter your choice: ");
                int userChoice;
                scanf("%d", &userChoice);

                switch (userChoice) {
                    case 1: {
                        displayProducts(productHashTable);
                        printf("Enter PID of the product to browse: ");
                        int browsePID;
                        scanf("%d", &browsePID);
                        trackBrowsing(browsingHistory, browsePID);
                        printf("Browsed product with PID: %d\n", browsePID);
                        findProduct(browsePID, productHashTable);
                        break;
                    }

                    case 2: {
                      displayProducts(productHashTable);
                      printf("Enter PID of the product to purchase: ");
                      int purchasePID;
                      scanf("%d", &purchasePID);
                      trackPurchase(purchaseHistory, purchasePID);
                      addPurchasedProduct(currentUser, purchasePID);
                      printf("Purchased product with PID: %d\n", purchasePID);

                      updateGraph(userGraph, currentUser->userID, purchasePID);
                      break;
                    }
                  
                    case 3:
                        printf("Browsing History:\n");
                        displayBrowsingHistory(userID, usersHashTable);
                        break;

                    case 4:
                        printf("Purchase History:\n");
                        displayPurchaseHistory(userID, usersHashTable);
                        break;

                    case 5:
                        recommendProducts(userGraph, currentUser->userID);
                        break;

                    case 6:
                        printf("Logged out of UserID: %d\n", currentUser->userID);
                        currentUser = NULL;
                        goto MAIN_MENU;

                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            }
        }
    MAIN_MENU:;
    }

    return 0;
}
