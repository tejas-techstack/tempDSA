#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int PID; 
    struct Node* left;
    struct Node* right;
} Node;

typedef struct SplayTree {
    Node* root;
    
} SplayTree;

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->PID = key;
    node->left = node->right = NULL;
    return node;  
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;  
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == NULL || root->PID == key)
        return root;

    if (root->PID > key) {
        if (root->left == NULL)
            return root;

        if (root->left->PID > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->PID < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        if (root->right == NULL)
            return root;

        if (root->right->PID > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        } else if (root->right->PID < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

Node* insertRecursive(Node* root, int PID) {
    if (root == NULL) {
        return newNode(PID); 
    }

    if (PID < root->PID) {
        root->left = insertRecursive(root->left, PID);
    } else {
        root->right = insertRecursive(root->right, PID);
    }

    return root; 
}

void insert(SplayTree *tree, int PID) {
    tree->root = insertRecursive(tree->root, PID); 
    tree->root = splay(tree->root, PID); 
}

void trackBrowsing(SplayTree *browsingHistory, int PID) {
    insert(browsingHistory, PID);
}

void trackPurchase(SplayTree *purchaseHistory, int PID) {
    insert(purchaseHistory, PID);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->PID);
        inorder(root->right);
    }
}

