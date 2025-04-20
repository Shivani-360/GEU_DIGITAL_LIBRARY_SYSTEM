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

typedef struct {
    char name[50];
    int id;
    char title[50];
} Student;

// ── Function Prototypes ──────────────────────────────────────────
int  login();
int  loadBooks(Book books[]);
void saveBooks(Book books[], int count);
void saveStudent(Student s);
void issueBook();

// ── Main ─────────────────────────────────────────────────────────
int main() {
    if (!login()) {
        printf("Invalid credentials. Exiting.\n");
        return 0;
    }
    issueBook();
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
        count++;
        if (count >= MAX) break;
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

void saveStudent(Student s) {
    FILE *f = fopen("students.txt", "a");
    fprintf(f, "%s|%d|%s\n", s.name, s.id, s.title);
    fclose(f);
}

// ── Issue Book ────────────────────────────────────────────────────
void issueBook() {
    Book books[MAX];
    int count = loadBooks(books);
    if (count == 0) {
        printf("No books to issue.\n");
        return;
    }

    char title[50], author[50];
    printf("Enter book title to issue: ");
    scanf(" %[^\n]", title);
    printf("Enter author name: ");
    scanf(" %[^\n]", author);

    // Search & issue
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0 &&
            strcmp(books[i].author, author) == 0) {
            if (books[i].available) {
                books[i].available = 0;
                Student s;
                printf("Enter student name: ");
                scanf(" %[^\n]", s.name);
                printf("Enter student ID: ");
                scanf("%d", &s.id);
                strcpy(s.title, title);
                saveStudent(s);
                saveBooks(books, count);
                printf("Book issued successfully to %s.\n", s.name);
                return;
            } else {
                printf(" Book is already issued.\n");
                return;
            }
        }
    }

    // Not found → suggest by subject
    printf(" Book not found. Searching similar subjects.\n");
    char subject[50];
    printf("Enter subject to search: ");
    scanf(" %[^\n]", subject);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].subject, subject) == 0 && books[i].available) {
            printf("Available: %s by %s\n",
                   books[i].title, books[i].author);
            found = 1;
        }
    }
    if (!found) printf("No available books found for subject '%s'.\n", subject);
}
