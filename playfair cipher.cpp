#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(char key[], char keyTable[SIZE][SIZE]) {
    char *keyPtr = key;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Ignoring 'J'
    int alphabetIndex[26] = {0}; // To keep track of which alphabet letters have been used

    // Fill the key table with the key
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (*keyPtr != '\0') {
                if (*keyPtr == 'J') {
                    keyPtr++; // Skip 'J' and continue with the key
                }
                keyTable[i][j] = toupper(*keyPtr++);
                alphabetIndex[keyTable[i][j] - 'A'] = 1;
            }
        }
    }

    // Fill the remaining spaces with unused alphabet letters
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == 0) {
                while (alphabetIndex[index]) {
                    index++;
                }
                keyTable[i][j] = alphabet[index++];
            }
        }
    }
}

void findPosition(char keyTable[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') {
        findPosition(keyTable, 'I', row, col); // Treat 'J' as 'I'
    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (keyTable[i][j] == ch) {
                    *row = i;
                    *col = j;
                    return;
                }
            }
        }
    }
}

void encrypt(char keyTable[SIZE][SIZE], char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    int i = 0;
    int row1, col1, row2, col2;

    while (i < len) {
        // Find positions of current and next characters in the key table
        findPosition(keyTable, plaintext[i], &row1, &col1);
        findPosition(keyTable, plaintext[i + 1], &row2, &col2);

        // Same row, wrap around columns
        if (row1 == row2) {
            ciphertext[i] = keyTable[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = keyTable[row2][(col2 + 1) % SIZE];
        }
        // Same column, wrap around rows
        else if (col1 == col2) {
            ciphertext[i] = keyTable[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = keyTable[(row2 + 1) % SIZE][col2];
        }
        // Forming a rectangle
        else {
            ciphertext[i] = keyTable[row1][col2];
            ciphertext[i + 1] = keyTable[row2][col1];
        }

        i += 2; // Move to the next pair of characters
    }
    ciphertext[len] = '\0'; // Add null terminator
}

int main() {
    char key[26];
    char plaintext[100];
    char ciphertext[100];
    char keyTable[SIZE][SIZE] = {0}; // Initialize key table with zeros

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    // Prepare the key table
    prepareKey(key, keyTable);

    // Encrypt the plaintext
    encrypt(keyTable, plaintext, ciphertext);

    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}
