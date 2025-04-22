#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Helper function for modular exponentiation (for demonstration purposes)
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// Simplified RSA Key Generation (very insecure for demonstration only)
std::pair<std::pair<long long, long long>, std::pair<long long, long long>> generateKeys() {
    // In reality, p and q should be large prime numbers
    long long p = 11;
    long long q = 13;
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    long long e = 7; // Public exponent (should be coprime to phi_n)
    long long d = 0; // Private exponent

    // Find d such that (e * d) % phi_n == 1 (using a simple loop for demonstration)
    for (long long i = 1; i < phi_n; ++i) {
        if ((e * i) % phi_n == 1) {
            d = i;
            break;
        }
    }

    return {{n, e}, {n, d}}; // {{n, e} = public, {n, d} = private}
}

// Simplified Signing Function (not cryptographically secure)
std::vector<long long> signData(const std::string& data, long long n, long long d) {
    std::vector<long long> signature;
    for (char c : data) {
        signature.push_back(power(static_cast<long long>(c), d, n));
    }
    return signature;
}

// Simplified Verification Function (not cryptographically secure)
bool verifySignature(const std::string& originalData, const std::vector<long long>& signature, long long n, long long e) {
    if (originalData.length() != signature.size()) {
        return false;
    }
    for (size_t i = 0; i < originalData.length(); ++i) {
        if (static_cast<long long>(originalData[i]) != power(signature[i], e, n)) {
            return false;
        }
    }
    return true;
}

int main() {
    // 1. Generate Key Pair
    auto keyPair = generateKeys();
    auto publicKey = keyPair.first;
    auto privateKey = keyPair.second;

    long long n = publicKey.first;
    long long e_pub = publicKey.second;
    long long d_priv = privateKey.second;

    std::string patientData = "Sensitive Patient Information";
    std::cout << "Original Patient Data: " << patientData << std::endl;

    // 2. Sign Encrypted Data (Let's assume the data is already encrypted - we'll just sign the plaintext for simplicity)
    std::vector<long long> digitalSignature = signData(patientData, n, d_priv);

    std::cout << "Digital Signature: ";
    for (long long sig : digitalSignature) {
        std::cout << sig << " ";
    }
    std::cout << std::endl;

    // Simulate sending the encrypted data and signature to an external partner

    // 3. Verify Signature
    std::string receivedData = patientData; // Assume the data was transmitted (and potentially encrypted)
    bool isSignatureValid = verifySignature(receivedData, digitalSignature, n, e_pub);

    if (isSignatureValid) {
        std::cout << "Signature is valid. Data is authentic and has not been tampered with." << std::endl;
    } else {
        std::cout << "Signature is invalid. Data may have been tampered with or is not from the expected provider." << std::endl;
    }

    // Simulate tampering with the data
    std::string tamperedData = "Altered Patient Information";
    bool isTamperedSignatureValid = verifySignature(tamperedData, digitalSignature, n, e_pub);

    if (isTamperedSignatureValid) {
        std::cout << "Signature is valid for tampered data (this should not happen with proper cryptography)." << std::endl;
    } else {
        std::cout << "Signature is invalid for tampered data (as expected)." << std::endl;
    }

    return 0;
}