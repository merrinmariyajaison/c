#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_ENTRIES 100

// Define a structure for a phone book entry
struct PhoneBookEntry {
    char name[MAX_NAME_LENGTH];
    char phone_number[10]; 
    struct PhoneBookEntry *next;
};

struct PhoneBookEntry *head =NULL;

// Function prototypes
void addEntry(const char* name, char phoneNumber[]); 
void addOrUpdateEntry(struct PhoneBookEntry[], int*, const char*, char[]);
void searchEntry(const char*);
void editEntry(const char*, const char*, char[]);
void deleteEntry(const char*);
void displayAllEntries();

int main() {
    struct PhoneBookEntry phoneBook[MAX_ENTRIES];
    int numEntries = 0;

    int choice;
    while (1) {
        printf("\nPhone Book Application\n");
        printf("1. Add or Update Entry\n");
        printf("2. Search Entry\n");
        printf("3. Edit Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Display All Entries\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                {
                    char name[MAX_NAME_LENGTH];
                    char phoneNumber[10];
                    printf("Enter Name: ");
                    if (scanf("%s", name) != 1) {
                        printf("Invalid input. Please enter a valid name.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    phoneinput:
                    printf("Enter Phone Number: ");
                    scanf("%s", phoneNumber);
				    int i;
    				int isInvalid = 0;
    				for (i = 0; i < strlen(phoneNumber); i++) {
        				if (!isdigit(phoneNumber[i])) {
            				isInvalid = 1;
            				break;
        				}
    				}
                    if (isInvalid ) {
        				printf("Error: Enter a valid phone number.\n");
        				goto phoneinput;
    				}
                    addEntry(name, phoneNumber);
                }
                break;

            case 2:
                {
                    char searchName[MAX_NAME_LENGTH];
                    printf("Enter Name to Search: ");
                    if (scanf("%s", searchName) != 1) {
                        printf("Invalid input. Please enter a valid name.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    searchEntry(searchName);
                }
                break;

            case 3:
                {
                    char nameToEdit[MAX_NAME_LENGTH];
                    char newName[MAX_NAME_LENGTH];
                    char newPhoneNumber[10];
                    printf("Enter Name to Edit: ");
                    if (scanf("%s", nameToEdit) != 1) {
                        printf("Invalid input. Please enter a valid name.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    printf("Enter New Name: ");
                    if (scanf("%s", newName) != 1) {
                        printf("Invalid input. Please enter a valid name.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    printf("Enter New Phone Number: ");
                    phoneinput2:
                    scanf("%s", newPhoneNumber);
				    int i;
    				int isInvalid = 0;
    				for (i = 0; i < strlen(newPhoneNumber); i++) {
        				if (!isdigit(newPhoneNumber[i])) {
            				isInvalid = 1;
            				break;
        				}
    				}
                    if (isInvalid ) {
        				printf("Error: Enter a valid phone number.\n");
        				goto phoneinput2;
    				}
                    editEntry(nameToEdit, newName, newPhoneNumber);
                }
                break;

            case 4:
                {
                    char nameToDelete[MAX_NAME_LENGTH];
                    printf("Enter Name to Delete: ");
                    if (scanf("%s", nameToDelete) != 1) {
                        printf("Invalid input. Please enter a valid name.\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    char confirmation;
                    printf("Are you sure you want to delete %s? (y/n): ", nameToDelete);
                    while (1) {
                        scanf(" %c", &confirmation);
                        if (confirmation == 'y' || confirmation == 'Y') {
                            deleteEntry(nameToDelete);
                            break;
                        } else if (confirmation == 'n' || confirmation == 'N') {
                            printf("Deletion canceled.\n");
                            break;
                        } else {
                            printf("Invalid input. Please enter 'y' or 'n': ");
                        }
                    }
                }
                break;

            case 5:
                displayAllEntries(phoneBook, numEntries);
                break;

            case 6:
                printf("Exiting Phone Book Application. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add or update an entry to the phone book
void addOrUpdateEntry(struct PhoneBookEntry phoneBook[], int* numEntries, const char* name, char phoneNumber[]) {
    int found = 0;
    int i;
    for ( i = 0; i < *numEntries; i++) {
        if (strcmp(phoneBook[i].name, name) == 0) {
            char confirmation;
            printf("Contact with the name '%s' already exists. Do you want to update it? (y/n): ", name);
            while (1) {
                scanf(" %c", &confirmation);
                if (confirmation == 'y' || confirmation == 'Y') {
                    strcpy(phoneBook[i].phone_number, phoneNumber);
                    printf("Entry updated successfully!\n");
                    found = 1;
                    break;
                } else if (confirmation == 'n' || confirmation == 'N') {
                    found = 1;
                    break;
                } else {
                    printf("Invalid input. Please enter 'y' or 'n': ");
                }
            }
        }
    }

    if (!found) {
        if (*numEntries >= MAX_ENTRIES) {
            printf("Phone book is full. Cannot add more entries.\n");
        } else {
            strcpy(phoneBook[*numEntries].name, name);
            strcpy(phoneBook[*numEntries].phone_number, phoneNumber);
            (*numEntries)++;
            printf("Contact added successfully!\n");
        }
    }
}

void addEntry(const char* name, char phoneNumber[]) {
	struct 	PhoneBookEntry *temp,*t;
	temp = (struct 	PhoneBookEntry *)malloc(sizeof(struct PhoneBookEntry));
	strcpy(temp->name,name);
	strcpy(temp->phone_number, phoneNumber);
	temp->next = NULL;
	if(head == NULL)
	{
		head  = temp;
	}
	else
	{
		t= head;
		while(t->next != NULL)
		{
			t=t->next;
		}
		t->next = temp;
	}
}

// Function to search for an entry in the phone book
void searchEntry(const char* searchName) {
    if (head == NULL) {
        printf("Phone book is empty.\n");
    } else {
        struct PhoneBookEntry *t = head;
        while(t!=NULL && strcmp(t->name,searchName)!=0){
        	t=t->next;
    	}
    	if(t==NULL)
    	{
    		 printf("Entry not found.\n");
		}
		else
		{
			printf("Name: %s\n", t->name);
            printf("Phone Number: %s\n",t->phone_number);
		}
    }
}

// Function to edit an entry in the phone book
void editEntry(const char* nameToEdit, const char* newName, char newPhoneNumber[]) {
    if (head == NULL) {
        printf("Phone book is empty.\n");
    }
	else {
        struct PhoneBookEntry *t = head;
        while(t!=NULL && strcmp(t->name,nameToEdit)!=0){
        	t=t->next;
    	}
    	if(t==NULL)
    	{
    		 printf("Entry not found.\n");
		}
		else
		{
			strcpy(t->name, newName);
            strcpy(t->phone_number, newPhoneNumber);
            printf("Entry edited successfully!\n");
		}
    }
}

// Function to delete an entry from the phone book
void deleteEntry(const char* nameToDelete) {
	
	if (head == NULL) {
        printf("Phone book is empty.\n");
    }
	else if(strcmp(head->name,nameToDelete)==0){
		head=head->next;
		printf("Entry deleted successfully!\n");
	}
	else
	{
	    struct PhoneBookEntry *t = head;
        while(t->next!=NULL && strcmp(t->next->name,nameToDelete)!=0){
        	t=t->next;
    	}
    	if(t->next==NULL)
    	{
    		 printf("Entry not found.\n");
		}
		else
		{
			t->next=t->next->next;
            printf("Entry deleted successfully!\n");
		}
    }
}

// Function to display all entries in the phone book
void displayAllEntries() {
	struct PhoneBookEntry *t;
    if (head == NULL) {
        printf("Phone book is empty.\n");
    }
	else 
	{
        printf("Phone Book Entries:\n");
        t=head;
        while(t!=NULL)
        {
        	printf("Name: %s\n", t->name);
            printf("Phone Number: %s\n", t->phone_number);
            printf("-------------------------\n");
            t=t->next;
		}
        
    }
}

