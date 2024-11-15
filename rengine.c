#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_RECOMMENDATIONS 10

typedef struct Node {
    int productID;
    struct Node *left, *right;
} Node;

typedef struct SplayTree {
    Node *root;
} SplayTree;

typedef struct User {
    int userID;
    char name[100];
    char email[100];
    SplayTree browsingHistory;
    SplayTree purchaseHistory;
    int flag;
} User;

int hash(int userID) {
    return userID % MAX_USERS;
}

int linear_probing(int hashValue, int i) {
    return (hashValue + i) % MAX_USERS;
}

Node *newNode(int productID) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->productID = productID;
    node->left = node->right = NULL;
    return node;
}

Node *rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node *splay(Node *root, int productID) {
    if (!root || root->productID == productID)
        return root;

    if (productID < root->productID) {
        if (!root->left) return root;

        if (productID < root->left->productID) {
            root->left->left = splay(root->left->left, productID);
            root = rightRotate(root);
        } else if (productID > root->left->productID) {
            root->left->right = splay(root->left->right, productID);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return (root->left) ? rightRotate(root) : root;
    } else {
        if (!root->right) return root;

        if (productID > root->right->productID) {
            root->right->right = splay(root->right->right, productID);
            root = leftRotate(root);
        } else if (productID < root->right->productID) {
            root->right->left = splay(root->right->left, productID);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return (root->right) ? leftRotate(root) : root;
    }
}

Node *insert(Node *root, int productID) {
    if (!root)
        return newNode(productID);

    root = splay(root, productID);

    if (root->productID == productID)
        return root;

    Node *new = newNode(productID);

    if (productID < root->productID) {
        new->right = root;
        new->left = root->left;
        root->left = NULL;
    } else {
        new->left = root;
        new->right = root->right;
        root->right = NULL;
    }
    return new;
}

void trackBrowsing(SplayTree *tree, int productID) {
    tree->root = insert(tree->root, productID);
}

void trackPurchase(SplayTree *tree, int productID) {
    tree->root = insert(tree->root, productID);
}

void addUser(int userID, char *name, char *email, User *userTable) {
    int i = 0;
    int hashValue = hash(userID);
    while (userTable[hashValue].flag != 0 && userTable[hashValue].userID != userID && i < MAX_USERS) {
        i++;
        hashValue = linear_probing(hashValue, i);
    }

    if (userTable[hashValue].flag == 0) {
        userTable[hashValue].flag = 1;
        userTable[hashValue].userID = userID;
        strcpy(userTable[hashValue].name, name);
        strcpy(userTable[hashValue].email, email);
        userTable[hashValue].browsingHistory.root = NULL;
        userTable[hashValue].purchaseHistory.root = NULL;
        printf("User added successfully: %s (%d)\n", name, userID);
    } else {
        printf("UserID %d already exists!\n", userID);
    }
}

void recommendProducts(SplayTree *browsingHistory, SplayTree *purchaseHistory) {
    printf("Recommendations based on browsing history:\n");
    if (browsingHistory->root) {
        printf("  - Product ID: %d\n", browsingHistory->root->productID);
    }
    printf("Recommendations based on purchase history:\n");
    if (purchaseHistory->root) {
        printf("  - Product ID: %d\n", purchaseHistory->root->productID);
    }
}

int main() {
    User userTable[MAX_USERS] = {0};

    addUser(101, "Alice", "alice@example.com", userTable);
    addUser(102, "Bob", "bob@example.com", userTable);

    trackBrowsing(&userTable[hash(101)].browsingHistory, 201);
    trackBrowsing(&userTable[hash(101)].browsingHistory, 202);
    trackPurchase(&userTable[hash(101)].purchaseHistory, 301);

    printf("\nUser Recommendations:\n");
    recommendProducts(&userTable[hash(101)].browsingHistory, &userTable[hash(101)].purchaseHistory);

    return 0;
}