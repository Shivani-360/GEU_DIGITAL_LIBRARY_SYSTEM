//BOOKS LOGIN
// book.c
#include <stdio.h>
#include "book.h"

void addBook() {
    FILE *f = fopen("books.txt", "a");
    if (!f) {
        printf("Error opening books.txt\n");
        return;
    }

    int id;
    char title[100];
    char author[100];

    printf("Enter book ID: ");
    scanf("%d", &id);
    getchar();  // clear newline
    printf("Enter book title: ");
    fgets(title, sizeof(title), stdin);
    printf("Enter author: ");
    fgets(author, sizeof(author), stdin);

    // remove newlines
    title[strcspn(title, "\n")] = '\0';
    author[strcspn(author, "\n")] = '\0';

    fprintf(f, "%d %s %s\n", id, title, author);
    fclose(f);

    printf("Book added successfully!\n");
}

void viewBooks() {
    FILE *f = fopen("books.txt", "r");
    if (!f) {
        printf("No books found.\n");
        return;
    }

    int id;
    char title[100], author[100];

    printf("\n=== Book List ===\n");

    while (fscanf(f, "%d %s %s", &id, title, author) != EOF) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\n\n", id, title, author);
    }

    fclose(f);
}
