#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct User
{
    int userID;
    char name[100];
    char email[100];
    int flag;
} User;


void init_hashtable(User *ht)
{
    for(int x = 0; x < MAX_SIZE ; x++)
        ht[x].flag = ht[x].userID = 0;
}


int hash(int userID)
{
    return userID % MAX_SIZE;
}

int linear_probing(int hashValue, int i)
{
    return (hashValue + i) % MAX_SIZE;
}

void addUser(int userID, char *name, char *email, User *ht)
{
    int i = 0;
    int hashValue = hash(userID);
    int index = hashValue;
    while(ht[hashValue].flag != 0 && ht[hashValue].userID != userID && i < MAX_SIZE)
    {
        i++;
        hashValue = linear_probing(index, i);
    }

    if(ht[hashValue].flag == 0 || ht[hashValue].userID == userID) 
    {
        ht[hashValue].flag = 1;
        ht[hashValue].userID = userID;
        strcpy(ht[hashValue].name, name);
        strcpy(ht[hashValue].email, email);
        printf("User has been created successfully\n");
    }
    else
    {
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


void updateUser(int userID, char *name, char *email, User *ht)
{
    User *user = search(userID, ht);
    if(user != NULL)
    {
        strcpy(user->name, name);
        strcpy(user->email, email);
        printf("User information updated successfully\n");
    }
    else
    {
        printf("User not found\n");
    }
}

void display(User *ht)
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(ht[i].flag != 0)
        {
            printf("Index %d : UserID: %d, Name: %s, Email: %s\n", i, ht[i].userID, ht[i].name, ht[i].email);
        }
    }
}

/*
int main()
{
    User hashTable[MAX_SIZE];
    init_hashtable(hashTable);

    int choice, userID;
    char name[100], email[100];
    User *user;

    while (1)
    {
        printf("\nUser Management System\n");
        printf("1. Add User\n");
        printf("2. Search User\n");
        printf("3. Update User\n");
        printf("4. Display All Users\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter UserID: ");
                scanf("%d", &userID);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Email: ");
                scanf("%s", email);
                addUser(userID, name, email, hashTable);
                break;
            case 2:
                printf("Enter UserID: ");
                scanf("%d", &userID);
                user = search(userID, hashTable);
                if (user != NULL)
                {
                    printf("User found - UserID: %d, Name: %s, Email: %s\n", user->userID, user->name, user->email);
                }
                else
                {
                    printf("User not found\n");
                }
                break;
            case 3:
                printf("Enter UserID: ");
                scanf("%d", &userID);
                int c;
                printf("Enter what you would like to update: \n1.Name\n2.Email ID\n");
                scanf("%d",&c);
                switch (c)
                {
                case 1:
                    printf("Enter New Name: ");
                    scanf("%s", name);
                    updateUser(userID, name, email, hashTable);
                    break;
                case 2:
                    printf("Enter New Email ID: ");
                    scanf("%s", email);
                    updateUser(userID, name, email, hashTable);
                    break;
                default:
                    break;
                }
            case 4:
                display(hashTable);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
*/
