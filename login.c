//lOGIN SYSTEM
// login.c
#include <stdio.h>
#include <string.h>
#include "login.h"

// Function to hash the password into a number
int simpleHash(char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % 100000;  // Basic hash logic
        str++;
    }
    return hash;
}

// Function to log in the user
int login() {
    char inputUsername[30];
    char inputPassword[30];
    int hashedInput;
    char storedUsername[30];
    int storedHash;
    int found = 0, attempts = 0;

    while (attempts < 3) {
        printf("Username: ");
        scanf("%s", inputUsername);
        printf("Password: ");
        scanf("%s", inputPassword);

        hashedInput = simpleHash(inputPassword); // Convert input password to hash

        FILE *f = fopen("users.txt", "r");  // Open user database
        if (!f) {
            printf("Error opening users.txt\n");
            return 0;
        }

        // Check each line in the file to see if the username and hashed password match
        while (fscanf(f, "%s %d", storedUsername, &storedHash) != EOF) {
            if (strcmp(inputUsername, storedUsername) == 0 && hashedInput == storedHash) {
                found = 1;
                break;
            }
        }
        fclose(f);

        if (found) {
            return 1;  // Login successful
        }

        printf("Invalid login. Try again.\n");
        attempts++;
    }

    return 0;  // Login failed
}
