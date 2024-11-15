#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct Node {
    int PID;
    int *name;
    int flag;
    char *category;
    int inventory;
} NODE;

void initialize_hashTable(NODE *hashTable) {
    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable[i].PID = 0;
        hashTable[i].name = NULL;
        hashTable[i].flag = 0;
        hashTable[i].category = NULL;
        hashTable[i].inventory = 0;
    }
}

void addProduct(int PID, const char *name, const char *category, int inventory, NODE *hashTable) {
    int hash, i = 0;
    hash = ((PID % MAX_SIZE) + i) % MAX_SIZE;
    while (hashTable[hash].flag != 0 && i < MAX_SIZE) {
        i++;
        hash = ((PID % MAX_SIZE) + i) % MAX_SIZE;
    }
    if (hashTable[hash].flag == 0) {
        hashTable[hash].PID = PID;
        hashTable[hash].name = strdup(name);
        hashTable[hash].flag = 1;
        hashTable[hash].category = strdup(category);
        hashTable[hash].inventory = inventory;
        printf("The data %d is inserted at %d\n", PID, hash);
    } else {
        printf("\nData cannot be inserted\n");
    }
}

int findProduct(int PID, NODE *hashTable) {
    int hash, i = 0;
    hash = ((PID % MAX_SIZE) + i) % MAX_SIZE;
    while (i < MAX_SIZE) {
        if (hashTable[hash].flag == 1 && hashTable[hash].PID == PID) {
            printf("\nThe product is found:\nPID: %d\nProduct Name: %s\nCategory: %s\nInventory: %d\n",
                   hashTable[hash].PID, hashTable[hash].name, hashTable[hash].category, hashTable[hash].inventory);
            return hash;
        }
        i++;
        hash = ((PID % MAX_SIZE) + i) % MAX_SIZE;
    }
    printf("\nData not found\n");
    return -1;
}

int updateProduct(int PID,const char *newName, const char *newCategory, int newInventory, NODE *hashTable) {
    int prodLocation = findProduct(PID, hashTable);
    if (prodLocation == -1) {
        return 1;
    } else {
        printf("\nUpdating Value...\n");
    }

    free(hashTable[prodLocation].category);
    free(hashTable[prodLocation].name);
    hashTable[prodLocation].name = strdup(newName);
    hashTable[prodLocation].category = strdup(newCategory);
    hashTable[prodLocation].inventory = newInventory;

    printf("\nValue Updated.\n");
    return 0;
}

void displayProductDB(NODE *hashTable) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hashTable[i].flag == 1) {
            printf("PID: %d,name: %s, Category: %s, Inventory: %d\n",hashTable[i].PID,hashTable[i].name, hashTable[i].category, hashTable[i].inventory);
        }
    }
}

