#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_PRODUCTS 100 

typedef struct User {
    int userID;
    char name[100];
    char email[100];
    int flag;
    int browsedProducts[MAX_PRODUCTS]; 
    int purchasedProducts[MAX_PRODUCTS]; 
    int browsedCount;
    int purchasedCount; 
} User;

void init_hashtable(User *ht) {
    for (int x = 0; x < MAX_SIZE; x++) {
        ht[x].flag = 0;
        ht[x].userID = 0;
        ht[x].browsedCount = 0;
        ht[x].purchasedCount = 0;
    }
}

int hash(int userID) {
    return userID % MAX_SIZE;
}

int linear_probing(int hashValue, int i) {
    return (hashValue + i) % MAX_SIZE;
}

void addUser(int userID, char *name, char *email, User *ht) {
    int i = 0;
    int hashValue = hash(userID);
    int index = hashValue;
    while (ht[hashValue].flag != 0 && ht[hashValue].userID != userID && i < MAX_SIZE) {
        i++;
        hashValue = linear_probing(index, i);
    }

    if (ht[hashValue].flag == 0 || ht[hashValue].userID == userID) {
        ht[hashValue].flag = 1;
        ht[hashValue].userID = userID;
        strcpy(ht[hashValue].name, name);
        strcpy(ht[hashValue].email, email);
        ht[hashValue].browsedCount = 0; 
        ht[hashValue].purchasedCount = 0;
        printf("User has been created successfully\n");
    } else {
        printf("User cannot be created\n");
    }
}

User *search(int userID, User *ht) {
    int i = 0;
    int hashValue = hash(userID);
    int index = hashValue;
    while (ht[hashValue].flag != 0 && i < MAX_SIZE) {
        if (ht[hashValue].userID == userID) {
            printf("User found - UserID: %d, Name: %s, Email: %s\n", ht[hashValue].userID, ht[hashValue].name, ht[hashValue].email);
            return &ht[hashValue];
        }
        i++;
        hashValue = linear_probing(index, i);
    }
    printf("User not found\n");
    return NULL;
}

void updateUser(int userID, char *name, char *email, User *ht) {
    User *user = search(userID, ht);
    if (user != NULL) {
        strcpy(user->name, name);
        strcpy(user->email, email);
        printf("User information updated successfully\n");
    } else {
        printf("User not found\n");
    }
}

void display(User *ht) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (ht[i].flag != 0) {
            printf("Index %d : UserID: %d, Name: %s, Email: %s\n", i, ht[i].userID, ht[i].name, ht[i].email);
            printf("Browsed Products: ");
            for (int j = 0; j < ht[i].browsedCount; j++) {
                printf("%d ", ht[i].browsedProducts[j]);
            }
            printf("\nPurchased Products: ");
            for (int j = 0; j < ht[i].purchasedCount; j++) {
                printf("%d ", ht[i].purchasedProducts[j]);
            }
            printf("\n");
        }
    }
}
void addBrowsedProduct(User *user, int productID) {
    if (user->browsedCount < MAX_PRODUCTS) {
        user->browsedCount++;
    } else {
        printf("Replacing the oldest browsed product for UserID: %d\n", user->userID);
    }
    for (int i = user->browsedCount - 1; i > 0; i--) {
        user->browsedProducts[i] = user->browsedProducts[i - 1];
    }
    user->browsedProducts[0] = productID;
}

void addPurchasedProduct(User *user, int productID) {
    if (user->purchasedCount < MAX_PRODUCTS) {
        user->purchasedCount++;
    } else {
        printf("Replacing the oldest purchased product for UserID: %d\n", user->userID);
    }
    for (int i = user->purchasedCount - 1; i > 0; i--) {
        user->purchasedProducts[i] = user->purchasedProducts[i - 1];
    }
    user->purchasedProducts[0] = productID;
}


void trackUserActivity(User *user, int browsedProductID, int purchasedProductID) {
    addBrowsedProduct(user, browsedProductID);
    addPurchasedProduct(user, purchasedProductID);
}

