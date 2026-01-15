#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define NAME_LENGTH 30

typedef struct Friend {
int id;
struct Friend* next;
} Friend;

typedef struct User {
int id;
char name[NAME_LENGTH];
Friend* friendList;
} User;

User users[MAX_USERS];
int userCount = 0;

int findUserId(char* name) {
	int i;
for ( i = 0; i < userCount; i++) {

if (strcmp(users[i].name, name) == 0) {
return i;
}
}
return -1;
}

void addUser(char* name) {
if (userCount >= MAX_USERS) {
printf("User limit reached.\n");
return;
}

if (findUserId(name) != -1) {
printf("User '%s' already exists.\n", name);
return;
}

strcpy(users[userCount].name, name);
users[userCount].id = userCount;
users[userCount].friendList = NULL;
userCount++;

printf("User '%s' added successfully!\n", name);

}

void addFriendship(char* name1, char* name2) {
int id1 = findUserId(name1);
int id2 = findUserId(name2);

if (id1 == -1 || id2 == -1) {
printf("One or both users not found.\n");
return;
}

if (id1 == id2) {
printf("Cannot add self as friend.\n");
return;
}

Friend* temp = users[id1].friendList;
while (temp != NULL) {
if (temp->id == id2) {
printf("%s and %s are already friends.\n", name1, name2);
return;
}
temp = temp->next;
}

Friend* newFriend1 = (Friend*)malloc(sizeof(Friend));
newFriend1->id = id2;
newFriend1->next = users[id1].friendList;
users[id1].friendList = newFriend1;

Friend* newFriend2 = (Friend*)malloc(sizeof(Friend));
newFriend2->id = id1;
newFriend2->next = users[id2].friendList;
users[id2].friendList = newFriend2;

printf("%s and %s are now friends!\n", name1, name2);
}

void displayFriends(char* name) {
int id = findUserId(name);
if (id == -1) {
printf("User not found.\n");
return;
}

printf("Friends of %s:\n", name);
Friend* temp = users[id].friendList;
if (temp == NULL) {

printf("No friends yet.\n");
} else {
while (temp != NULL) {
printf("- %s\n", users[temp->id].name);
temp = temp->next;
}
}
}

void suggestFriends(char* name) {
int id = findUserId(name);
if (id == -1) {
printf("User not found.\n");
return;
}

int suggestions[MAX_USERS] = {0};

Friend* friend = users[id].friendList;
while (friend != NULL) {
Friend* friendsFriend = users[friend->id].friendList;
while (friendsFriend != NULL) {
if (friendsFriend->id != id) {
suggestions[friendsFriend->id]++;

}
friendsFriend = friendsFriend->next;
}
friend = friend->next;
}

friend = users[id].friendList;
while (friend != NULL) {
suggestions[friend->id] = 0;
friend = friend->next;
}
suggestions[id] = 0;

printf("Friend suggestions for %s:\n", name);
int found = 0, i;
for (i = 0; i < userCount; i++) {
if (suggestions[i] > 0) {
printf("- %s (%d mutual friends)\n", users[i].name,
suggestions[i]);
found = 1;
}
}

if (!found) {

printf("No suggestions available.\n");
}
}

void freeMemory() {
	int i;
    for (i = 0; i < userCount; i++) {
        Friend* temp = users[i].friendList;
        while (temp != NULL) {
            Friend* next = temp->next;
            free(temp);
            temp = next;
        }
    }
}


void menu() {
int choice;
char name1[NAME_LENGTH], name2[NAME_LENGTH];

do {
printf("\n--- Social Media Friend Suggestion ---\n");
printf("1. Add User\n");
printf("2. Add Friendship\n");
printf("3. View Friends\n");
printf("4. Suggest Friends\n");
printf("5. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);
getchar(); // to consume newline

switch (choice) {
case 1:
printf("Enter user name: ");
fgets(name1, NAME_LENGTH, stdin);
name1[strcspn(name1, "\n")] = 0;

addUser(name1);
break;

case 2:
printf("Enter first user name: ");
fgets(name1, NAME_LENGTH, stdin);
name1[strcspn(name1, "\n")] = 0;
printf("Enter second user name: ");
fgets(name2, NAME_LENGTH, stdin);
name2[strcspn(name2, "\n")] = 0;
addFriendship(name1, name2);
break;

case 3:
printf("Enter user name: ");
fgets(name1, NAME_LENGTH, stdin);
name1[strcspn(name1, "\n")] = 0;
displayFriends(name1);
break;

case 4:
printf("Enter user name: ");
fgets(name1, NAME_LENGTH, stdin);
name1[strcspn(name1, "\n")] = 0;

suggestFriends(name1);
break;

case 5:
printf("Exiting...\n");
break;

default:
printf("Invalid choice.\n");
}
} while (choice != 5);
}

int main() {
    menu();
    freeMemory();
    return 0;
}

