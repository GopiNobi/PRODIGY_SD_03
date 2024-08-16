#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 15
#define EMAIL_SIZE 50
#define FILENAME "contacts.dat"

typedef struct {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
} Contact;

void addContact(Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }

    printf("Enter Name: ");
    fgets(contacts[*count].name, NAME_SIZE, stdin);
    contacts[*count].name[strcspn(contacts[*count].name, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(contacts[*count].phone, PHONE_SIZE, stdin);
    contacts[*count].phone[strcspn(contacts[*count].phone, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(contacts[*count].email, EMAIL_SIZE, stdin);
    contacts[*count].email[strcspn(contacts[*count].email, "\n")] = '\0';

    (*count)++;
    printf("Contact added successfully!\n");
}

void viewContacts(Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Contact %d:\n", i + 1);
        printf("  Name: %s\n", contacts[i].name);
        printf("  Phone: %s\n", contacts[i].phone);
        printf("  Email: %s\n", contacts[i].email);
        printf("\n");
    }
}

int findContactByNameOrPhone(Contact contacts[], int count, const char *query) {
    for (int i = 0; i < count; i++) {
        // Debugging output
        printf("Checking contact %d: %s (%s)\n", i + 1, contacts[i].name, contacts[i].phone);
        // Compare the query with both name and phone
        if (strcasecmp(contacts[i].name, query) == 0 || strcmp(contacts[i].phone, query) == 0) {
            return i;
        }
    }
    return -1;
}

void editContact(Contact contacts[], int count) {
    char query[NAME_SIZE];

    printf("Enter the contact name or phone number to edit: ");
    fgets(query, NAME_SIZE, stdin);
    query[strcspn(query, "\n")] = '\0';

    int index = findContactByNameOrPhone(contacts, count, query);

    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    printf("Editing Contact: %s (%s)\n", contacts[index].name, contacts[index].phone);
    printf("Enter New Name: ");
    fgets(contacts[index].name, NAME_SIZE, stdin);
    contacts[index].name[strcspn(contacts[index].name, "\n")] = '\0';

    printf("Enter New Phone: ");
    fgets(contacts[index].phone, PHONE_SIZE, stdin);
    contacts[index].phone[strcspn(contacts[index].phone, "\n")] = '\0';

    printf("Enter New Email: ");
    fgets(contacts[index].email, EMAIL_SIZE, stdin);
    contacts[index].email[strcspn(contacts[index].email, "\n")] = '\0';

    printf("Contact updated successfully!\n");
}

void deleteContact(Contact contacts[], int *count) {
    char query[NAME_SIZE];

    printf("Enter the contact name or phone number to delete: ");
    fgets(query, NAME_SIZE, stdin);
    query[strcspn(query, "\n")] = '\0';

    int index = findContactByNameOrPhone(contacts, *count, query);

    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    printf("Deleting Contact: %s (%s)\n", contacts[index].name, contacts[index].phone);

    for (int i = index; i < *count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*count)--;
    printf("Contact deleted successfully!\n");
}

void saveContacts(Contact contacts[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Failed to open file for saving.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), count, file);
    fclose(file);
}

void loadContacts(Contact contacts[], int *count) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("No saved contacts found.\n");
        return;
    }

    fread(count, sizeof(int), 1, file);
    fread(contacts, sizeof(Contact), *count, file);
    fclose(file);
}

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;

    loadContacts(contacts, &count);

    while (1) {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1:
                addContact(contacts, &count);
                break;
            case 2:
                viewContacts(contacts, count);
                break;
            case 3:
                editContact(contacts, count);
                break;
            case 4:
                deleteContact(contacts, &count);
                break;
            case 5:
                saveContacts(contacts, count);
                printf("Contacts saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
