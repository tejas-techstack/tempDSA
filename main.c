#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "History.c"  // Assuming this contains the Splay Tree implementation
#include "users.c"    // Assuming this contains the User management implementation
#include "product.c"  // Assuming this contains the Product management implementation

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

int main() {
    SplayTree *browsingHistory = (SplayTree *)malloc(sizeof(SplayTree));
    browsingHistory->root = NULL;

    SplayTree *purchaseHistory = (SplayTree *)malloc(sizeof(SplayTree));
    purchaseHistory->root = NULL;

    User *usersHashTable = (User *)malloc(sizeof(User) * MAX_SIZE);
    init_hashtable(usersHashTable);

    NODE *productHashTable = (NODE *)malloc(sizeof(NODE) * MAX_SIZE);
    initialize_hashTable(productHashTable);

  
    addProduct(101, "Laptop", "Electronics", 50, productHashTable);
    addProduct(102, "Smartphone", "Electronics", 100, productHashTable);
    addProduct(103, "Headphones", "Accessories", 200, productHashTable);

    int userID;
    User *currentUser = NULL;


    while (1) {
        printf("Enter UserID to login (or 0 to create a new user): ");
        scanf("%d", &userID);

        if (userID == 0) {
 
            char name[100], email[100];
            printf("Enter Name: ");
            scanf("%s", name);
            printf("Enter Email: ");
            scanf("%s", email);
            addUser(userID, name, email, usersHashTable);
            currentUser = search(userID, usersHashTable);
            break;
        } else {
 
            currentUser = search(userID, usersHashTable);
            if (currentUser != NULL) {
                printf("Logged in as UserID: %d\n", currentUser->userID);
                break;
            } else {
                printf("User not found. Please try again.\n");
            }
        }
    }

  
    while (1) {
        int choice;
        printf("\n--- Menu ---\n");
        printf("1. Browse Products\n");
        printf("2. Purchase Product\n");
        printf("3. View Browsing History\n");
        printf("4. View Purchase History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                displayProducts(productHashTable);
                printf("Enter PID of the product to browse: ");
                int browsePID;
                scanf("%d", &browsePID);
                trackBrowsing(browsingHistory, browsePID);
                printf("Browsed product with PID: %d\n", browsePID);
                break;

            case 2: 
                displayProducts(productHashTable);
                printf("Enter PID of the product to purchase: ");
                int purchasePID;
                scanf("%d", &purchasePID);
                trackPurchase(purchaseHistory, purchasePID);
                addPurchasedProduct(currentUser, purchasePID); 
                printf("Purchased product with PID: %d\n", purchasePID);
                break;

            case 3: 
                printf("Browsing History:\n");
                inorder(browsingHistory->root);
                break;

            case 4: 
                printf("Purchase History:\n");
                inorder(purchaseHistory->root);
                break;

            case 5: 
                free(browsingHistory);
                free(purchaseHistory);
                free(usersHashTable);
                free(productHashTable);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}