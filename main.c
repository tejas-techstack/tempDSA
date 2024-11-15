#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "History.c"
#include "users.c"
#include "product.c"


#define MAX_SIZE 1000

int main(){
    SplayTree *browsingHistory = (SplayTree *)malloc(sizeof(SplayTree));
    browsingHistory->root = NULL;

    SplayTree *purchaseHistory = (SplayTree *)malloc(sizeof(SplayTree));
    purchaseHistory->root = NULL;

    User *usersHashTable = (User *)malloc(sizeof(User) * MAX_SIZE);
    init_hashtable(usersHashTable);

    Node *productHashTable = (Node *)malloc(sizeof(Node) * MAX_SIZE);
    initialize_hashTable(productHashTable);

    // Add products to productHashTable

    // Add users to usersHashTable

    // Add browsing history and purchase history

    // Print browsing history and purchase history

    free(browsingHistory);
    free(purchaseHistory);
    free(usersHashTable);
    free(productHashTable);
    
    return 0;
}