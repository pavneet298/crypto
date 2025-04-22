#include <iostream>
#include <vector>
#include <bitset>
#include <cstring>
#include <cstdint>
#include <iomanip> // Added for formatting output

using namespace std;

// 64-bit DES keys
const uint64_t key1 = 0x133457799BBCDFF1;
const uint64_t key2 = 0x1122334455667788;
const uint64_t key3 = 0xAABBCCDDEEFF0011;

// Initial Permutation Table (IP)
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table (FP)
const int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Function to apply permutation
uint64_t permute(uint64_t input, const int table[], int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1; // Corrected line
    }
    return output;
}

// DES round function (simplified XOR)
uint64_t des_round(uint64_t block, uint64_t key) {
    return block ^ key;
}

// Single DES encryption function
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    uint64_t permuted_text = permute(plaintext, IP, 64);
    uint64_t cipher = des_round(permuted_text, key);
    return permute(cipher, FP, 64);
}

// Single DES decryption function (same as encryption in this simplified case)
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t permuted_text = permute(ciphertext, IP, 64);
    uint64_t decrypted = des_round(permuted_text, key);
    return permute(decrypted, FP, 64);
}

// Triple DES Encryption in ECB Mode
uint64_t triple_des_encrypt(uint64_t plaintext) {
    uint64_t step1 = des_encrypt(plaintext, key1);
    uint64_t step2 = des_decrypt(step1, key2);
    uint64_t step3 = des_encrypt(step2, key3);
    return step3;
}

// Triple DES Decryption in ECB Mode
uint64_t triple_des_decrypt(uint64_t ciphertext) {
    uint64_t step1 = des_decrypt(ciphertext, key3);
    uint64_t step2 = des_encrypt(step1, key2);
    uint64_t step3 = des_decrypt(step2, key1);
    return step3;
}

int main() {
    uint64_t plaintext;
    cout << "Enter a 64-bit hexadecimal integer as plaintext: ";
    cin >> hex >> plaintext; // Use hex input

    // Encrypt
    uint64_t encrypted = triple_des_encrypt(plaintext);
    cout << "Encrypted Data  : " << hex << uppercase << encrypted << endl; // Use hex output
    cout << "Encrypted Data  : " << dec << encrypted << endl;

    // Decrypt
    uint64_t decrypted = triple_des_decrypt(encrypted);
    cout << "Decrypted Data  : " << hex << uppercase << decrypted << endl; // Use hex output
    cout << "Decrypted Data  : " << dec << decrypted << endl;

    return 0;
}
