// phonebook.c
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 11
#define MAX_EMAIL_LENGTH 50
#define PHONEBOOK_FILE "phonebook.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Contact;

void addContact(Contact contact) {
    FILE *fp = fopen(PHONEBOOK_FILE, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s,%s,%s\n", contact.name, contact.phone, contact.email);
    fclose(fp);
}

void updateContact(Contact contact) {
    FILE *fp = fopen(PHONEBOOK_FILE, "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, fp)) {
        char name[MAX_NAME_LENGTH];
        char phone[MAX_PHONE_LENGTH];
        char email[MAX_EMAIL_LENGTH];
        sscanf(line, "%[^,],%[^,],%[^\n]\n", name, phone, email);
        if (strcmp(name, contact.name) == 0) {
            fprintf(fp, "%s,%s,%s\n", contact.name, contact.phone, contact.email);
            break;
        }
    }
    fclose(fp);
}

void deleteContact(char *name) {
    FILE *fp = fopen(PHONEBOOK_FILE, "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, fp)) {
        char tempName[MAX_NAME_LENGTH];
        sscanf(line, "%[^,],%*[^,],%*[^,]\n", tempName);
        if (strcmp(tempName, name)!= 0) {
            fprintf(fp, "%s", line);
        }
    }
    fclose(fp);
}

void searchContact(char *name) {
    FILE *fp = fopen(PHONEBOOK_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, fp)) {
        char tempName[MAX_NAME_LENGTH];
        sscanf(line, "%[^,],%*[^,],%*[^,]\n", tempName);
        if (strcmp(tempName, name) == 0) {
            printf("%s", line);
            break;
        }
    }
    fclose(fp);
}

void displayAllContacts() {
    FILE *fp = fopen(PHONEBOOK_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[1024];
    while (fgets(line, 1024, fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

int validateName(char *name) {
    int i;
    for (i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }
    return 1;
}

int validatePhone(char *phone) {
    int i;
    if (strlen(phone)!= 10) {
        return 0;
    }
    for (i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

int validateEmail(char *email) {
    int atCount = 0;
    int dotCount = 0;
    int i;
    for (i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            atCount++;
        }
        if (email[i] == '.') {
            dotCount++;
        }
    }
    if (atCount!= 1 || dotCount < 1) {
        return 0;
    }
    return 1;
}

int main() {
    int choice;
    Contact contact;
    char name[MAX_NAME_LENGTH];
    while (1) {
        printf("1. Add Contact\n");
        printf("2. Update Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Search Contact\n");
        printf("5. Display All Contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", contact.name);
                if (!validateName(contact.name)) {
                    printf("Invalid name!\n");
                    break;
                }
                printf("Enter phone number: ");
                scanf("%s", contact.phone);
                if (!validatePhone(contact.phone)) {
                    printf("Invalid phone number!\n");
                    break;
                }
                printf("Enter email address: ");
                scanf("%s", contact.email);
                addContact(contact);
                break;
            case 2:
                printf("Enter name of contact to update: ");
                scanf("%s", name);
                if (!validateName(name)) {
                    printf("Invalid name!\n");
                    break;
                }
                printf("Enter new phone number: ");
                scanf("%s", contact.phone);
                if (!validatePhone(contact.phone)) {
                    printf("Invalid phone number!\n");
                    break;
                }
                printf("Enter new email address: ");
                scanf("%s", contact.email);
                updateContact(contact);
                break;
            case 3:
                printf("Enter name of contact to delete: ");
                scanf("%s", name);
                if (!validateName(name)) {
                    printf("Invalid name!\n");
                    break;
                }
                deleteContact(name);
                break;
            case 4:
                printf("Enter name or phone number to search: ");
                scanf("%s", name);
                searchContact(name);
                break;
            case 5:
                displayAllContacts();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}