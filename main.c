// main.c
#include <stdio.h>
#include "login.h"
#include "book.h"

int main() {
    printf("=== Welcome to GEU Digital Library System ===\n");

    if (login()) {
        printf("Login successful!\n");

        int choice;
        do {
            printf("\n=== Library Menu ===\n");
            printf("1. Add Book\n");
            printf("2. View Books\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    viewBooks();
                    break;
                case 3:
                    printf("Exiting program...\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } while (choice != 3);

    } else {
        printf("Login failed. Exiting...\n");
    }

    return 0;
}
