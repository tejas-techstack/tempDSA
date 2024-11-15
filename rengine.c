#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct user {
    char id[30];
    char name[50];
    char email[50];
    struct user *next;
} User;

int hash(char *id) {
    int hash = 0;
    while (*id) {
        hash += *id++;
    }
    return hash % SIZE;
}

int add_user(User *table[], char *id, char *name, char *email) {
    int index = hash(id);
    User *new = (User *)malloc(sizeof(User));

    if (new == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    strcpy(new->id, id);
    strcpy(new->name, name);
    strcpy(new->email, email);
    new->next = table[index];
    table[index] = new;

    return 0;
}

User *get_user(User *table[], char *id) {
    int ind = hash(id);
    User *curr = table[ind];
    while (curr) {
        if (strcmp(curr->id, id) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

/*
int main() {
    User *table[SIZE] = {NULL};

    add_user(table, "001", "Alice", "alice@example.com");
    add_user(table, "002", "Bob", "bob@example.com");

    User *user = get_user(table, "001");
    if (user != NULL) {
        printf("User found: %s, %s\n", user->name, user->email);
    } else {
        printf("User not found.\n");
    }

    for (int i = 0; i < SIZE; i++) {
        User *curr = table[i];
        while (curr) {
            User *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return 0;
}
*/
