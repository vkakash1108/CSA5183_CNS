#include <stdio.h>
#include <stdint.h>

void initialPermutation(uint64_t *data) {
    
}


void finalPermutation(uint64_t *data) {
    
}


void generateSubkeys(uint64_t key, uint64_t *subkeys) {
    
}


void desRound(uint32_t *lef
t, uint32_t *right, uint64_t subkey) {
    
}


void desEncrypt(uint64_t plaintext, uint64_t key, uint64_t *ciphertext) {
    uint64_t subkeys[16];
    uint64_t data = plaintext;

    generateSubkeys(key, subkeys);
    initialPermutation(&data);

    uint32_t left = data >> 32;
    uint32_t right = data & 0xFFFFFFFF;

    for (int i = 0; i < 16; ++i) {
        desRound(&left, &right, subkeys[i]);
    }

    
    uint64_t encryptedData = ((uint64_t)right << 32) | left;
    finalPermutation(&encryptedData);

    *ciphertext = encryptedData;
}

int main() {
    uint64_t plaintext, key, ciphertext;

    printf("Enter 64-bit plaintext: ");
    scanf("%llx", &plaintext);

    printf("Enter 64-bit key: ");
    scanf("%llx", &key);

    desEncrypt(plaintext, key, &ciphertext);

    printf("Plaintext:  %016llX\n", plaintext);
    printf("Key:        %016llX\n", key);
    printf("Ciphertext: %016llX\n", ciphertext);

    return 0;
}
