#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50
#define DATA_FILE "library_data.bin"

typedef struct {
    int id;
    char title[100];
    char author[50];
    int qty;
} Book;

typedef struct {
    int id;
    char name[100];
    char phone[15];
} Member;

Book library[MAX_BOOKS];
Member members[MAX_MEMBERS];
int bookCount = 0;
int memberCount = 0;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void syncStorage() {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp) {
        fwrite(&bookCount, sizeof(int), 1, fp);
        fwrite(&memberCount, sizeof(int), 1, fp);
        fwrite(library, sizeof(Book), bookCount, fp);
        fwrite(members, sizeof(Member), memberCount, fp);
        fclose(fp);
    }
}

void loadStorage() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp) {
        fread(&bookCount, sizeof(int), 1, fp);
        fread(&memberCount, sizeof(int), 1, fp);
        fread(library, sizeof(Book), bookCount, fp);
        fread(members, sizeof(Member), memberCount, fp);
        fclose(fp);
    }
}

void addNewBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("\n[ALERT] Storage limit reached!\n");
        return;
    }

    int newID;
    printf("Enter Book ID: ");
    scanf("%d", &newID);
    clearBuffer();
    
    for(int i = 0; i < bookCount; i++) {
        if(library[i].id == newID) {
            printf("\n[ERROR] Book ID %d already exists in system!\n", newID);
            return; 
        }
    }
    
    library[bookCount].id = newID;

    printf("Enter Title: ");
    fgets(library[bookCount].title, 100, stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0; 

    printf("Enter Author: ");
    fgets(library[bookCount].author, 50, stdin);
    library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;

    printf("Enter Quantity: ");
    scanf("%d", &library[bookCount].qty);
    clearBuffer();
    
    bookCount++;
    syncStorage();
    printf("\n[SUCCESS] Record Saved.\n");
}

void showInventory() {
    if (bookCount == 0) {
        printf("\n[INFO] Inventory is currently empty.\n");
        return;
    }
    printf("\n%-5s %-30s %-20s %-5s", "ID", "TITLE", "AUTHOR", "QTY");
    printf("\n--------------------------------------------------------------");
    for(int i = 0; i < bookCount; i++) {
        printf("\n%-5d %-30s %-20s %-5d", library[i].id, library[i].title, library[i].author, library[i].qty);
    }
    printf("\n");
}

void issueBook() {
    int bID, mID, found = 0;
    printf("\n--- ISSUE BOOK ---");
    printf("\nEnter Book ID: ");
    scanf("%d", &bID);
    printf("Enter Member ID: ");
    scanf("%d", &mID);
    clearBuffer();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bID) {
            found = 1;
            if (library[i].qty > 0) {
                library[i].qty--;
                syncStorage(); 
                printf("\n[SUCCESS] Book ID %d issued to Member %d.\n", bID, mID);
            } else {
                printf("\n[ERROR] Book Out of Stock! Current Quantity: 0\n");
            }
            return;
        }
    }
    if (!found) printf("\n[ERROR] Book ID not found.\n");
}

void returnBook() {
    int bID, found = 0;
    printf("\n--- RETURN BOOK ---");
    printf("\nEnter Book ID to Return: ");
    scanf("%d", &bID);
    clearBuffer();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bID) {
            library[i].qty++;
            syncStorage();
            printf("\n[SUCCESS] Inventory Updated. New Qty: %d\n", library[i].qty);
            found = 1;
            return;
        }
    }
    if (!found) printf("\n[ERROR] Invalid Book ID.\n");
}

void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("\n[ALERT] Member limit reached!\n");
        return;
    }
    int mID;
    printf("Enter Member ID: ");
    scanf("%d", &mID);
    clearBuffer();

    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == mID) {
            printf("\n[ERROR] Member ID %d is already registered!\n", mID);
            return;
        }
    }
    members[memberCount].id = mID;

    printf("Enter Member Name: ");
    fgets(members[memberCount].name, 100, stdin);
    members[memberCount].name[strcspn(members[memberCount].name, "\n")] = 0;

    printf("Enter Contact Number: ");
    fgets(members[memberCount].phone, 15, stdin);
    members[memberCount].phone[strcspn(members[memberCount].phone, "\n")] = 0;

    memberCount++;
    syncStorage();
    printf("\n[SUCCESS] Member registered successfully.\n");
}

void searchBook() {
    if (bookCount == 0) {
        printf("\n[INFO] No books available to search.\n");
        return;
    }
    char query[100];
    int found = 0;
    printf("\nEnter Book Title or Author: ");
    fgets(query, 100, stdin);
    query[strcspn(query, "\n")] = 0;

    printf("\n%-5s %-30s %-20s %-5s", "ID", "TITLE", "AUTHOR", "QTY");
    printf("\n--------------------------------------------------------------");
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, query) || strstr(library[i].author, query)) {
            printf("\n%-5d %-30s %-20s %-5d", library[i].id, library[i].title, library[i].author, library[i].qty);
            found = 1;
        }
    }
    if (!found) printf("\nNo matching records found for '%s'.", query);
    printf("\n");
}

int main() {
    int choice;
    loadStorage();

    while(1) {
        printf("\n\n=== LIBMASTER MENU ===");
        printf("\n1. Add Book    2. View Books   3. Add Member");
        printf("\n4. Issue Book  5. Return Book  6. Search");
        printf("\n7. Exit");
        printf("\nAction > ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer(); 
            continue;
        }
        clearBuffer(); 

        switch(choice) {
            case 1: addNewBook(); break;
            case 2: showInventory(); break;
            case 3: addMember(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: searchBook(); break;
            case 7: syncStorage(); printf("\nData saved. Exiting...\n"); exit(0);
            default: printf("\nInvalid Option!");
        }

        printf("\n--- Task Complete. Press Enter to continue ---");
        getchar(); 
    }
    return 0;
}
