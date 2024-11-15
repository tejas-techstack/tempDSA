#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Graph {
    int numUsers;
    bool **adjMatrix;
    User *users;
} Graph;

Graph* createGraph(int numUsers, User *usersHashTable) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numUsers = numUsers;
    graph->users = usersHashTable;
    graph->adjMatrix = (bool **)calloc(numUsers, sizeof(bool *));
    for (int i = 0; i < numUsers; i++) {
        graph->adjMatrix[i] = (bool *)calloc(numUsers, sizeof(bool));
    }
    return graph;
}

void buildGraph(Graph *graph) {
    for (int i = 0; i < graph->numUsers; i++) {
        for (int j = i + 1; j < graph->numUsers; j++) {
            User *user1 = &graph->users[i];
            User *user2 = &graph->users[j];
            for (int k = 0; k < user1->purchasedCount; k++) {
                for (int l = 0; l < user2->purchasedCount; l++) {
                    if (user1->purchasedProducts[k] == user2->purchasedProducts[l]) {
                        graph->adjMatrix[i][j] = true;
                        graph->adjMatrix[j][i] = true;
                        goto nextPair; // Break both inner loops
                    }
                }
            }
        nextPair:
            ;
        }
    }
}

void recommendProducts(Graph *graph, int userID) {
    if (userID < 0 || userID >= graph->numUsers) {
        printf("Invalid UserID: %d\n", userID);
        return;
    }

    User *currentUser = &graph->users[userID];
    printf("Recommendations for UserID: %d\n", userID);

    bool *recommendedProducts = (bool *)calloc(1000, sizeof(bool)); 

    for (int i = 0; i < graph->numUsers; i++) {
        if (graph->adjMatrix[userID][i]) {
            User *neighbor = &graph->users[i];
            for (int j = 0; j < neighbor->purchasedCount; j++) {
                int productID = neighbor->purchasedProducts[j];
                bool alreadyPurchased = false;

                for (int k = 0; k < currentUser->purchasedCount; k++) {
                    if (currentUser->purchasedProducts[k] == productID) {
                        alreadyPurchased = true;
                        break;
                    }
                }

                if (!alreadyPurchased && !recommendedProducts[productID]) {
                    printf("Product ID: %d\n", productID);
                    recommendedProducts[productID] = true;
                }
            }
        }
    }

    free(recommendedProducts);
}
