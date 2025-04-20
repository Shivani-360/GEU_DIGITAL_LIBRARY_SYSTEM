#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ── Data Structures ───────────────────────────────────────────────
typedef struct {
    char subject[50];
    char title[50];
    char author[50];
    int available;    // 1 = available, 0 = issued
} Book;

// ── Function Prototypes ──────────────────────────────────────────
int  login();
int  loadBooks(Book books[]);
void saveBooks(Book books[], int count);
void applyFine();
void returnBook();

// ── Main ─────────────────────────────────────────────────────────
int main() {
    if (!login()) {
        printf("Invalid credentials. Exiting.\n");
        return 0;
    }
    returnBook();
    return 0;
}

// ── Admin Login ───────────────────────────────────────────────────
int login() {
    char user[20], pass[20];
    printf("=== ADMIN LOGIN ===\n");
    printf("Username: ");
    scanf("%19s", user);
    printf("Password: ");
    scanf("%19s", pass);
    return (strcmp(user, "admin") == 0 && strcmp(pass, "password") == 0);
}

// ── Load & Save Helpers ──────────────────────────────────────────
int loadBooks(Book books[]) {
    FILE *f = fopen("books.txt", "r");
    if (!f) {
        printf("Error: books.txt not found.\n");
        return 0;
    }
    int count = 0;
    while (fscanf(f, "%49[^|]|%49[^|]|%49[^|]|%d\n",
                  books[count].subject,
                  books[count].title,
                  books[count].author,
                  &books[count].available) != EOF) {
        if (++count >= MAX) break;
    }
    fclose(f);
    return count;
}

void saveBooks(Book books[], int count) {
    FILE *f = fopen("books.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s|%s|%s|%d\n",
                books[i].subject,
                books[i].title,
                books[i].author,
                books[i].available);
    }
    fclose(f);
}

void applyFine() {
    printf("Late fee applied: Rs. 10\n");
}

// ── Return Book ───────────────────────────────────────────────────
void returnBook() {
    Book books[MAX];
    int count = loadBooks(books);
    if (count == 0) {
        printf("No records to process.\n");
        return;
    }

    char title[50];
    printf("Enter the title of the book to return: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0 && books[i].available == 0) {
            books[i].available = 1;
            int late;
            printf("Was the return late? (1 = Yes / 0 = No): ");
            scanf("%d", &late);
            if (late) applyFine();
            saveBooks(books, count);
            printf("✅ Book returned successfully.\n");
            return;
        }
    }

    printf("⚠️  Book not found or it was not issued.\n");
}
