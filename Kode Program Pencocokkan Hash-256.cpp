#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>

// Konstanta untuk SHA-256
const unsigned int k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Fungsi-fungsi SHA-256
unsigned int rotr(unsigned int n, unsigned int x) { return (x >> n) | (x << (32 - n)); }
unsigned int choose(unsigned int e, unsigned int f, unsigned int g) { return (e & f) ^ (~e & g); }
unsigned int majority(unsigned int a, unsigned int b, unsigned int c) { return (a & b) ^ (a & c) ^ (b & c); }
unsigned int sig0(unsigned int x) { return rotr(7, x) ^ rotr(18, x) ^ (x >> 3); }
unsigned int sig1(unsigned int x) { return rotr(17, x) ^ rotr(19, x) ^ (x >> 10); }

std::vector<unsigned int> preprocess(const std::string &input) {
    std::vector<unsigned int> blocks;
    int original_length = input.size() * 8;
    std::string data = input + static_cast<char>(0x80);

    while (data.size() % 64 != 56) data += static_cast<char>(0x00);
    for (int i = 3; i >= 0; i--) data += static_cast<char>((original_length >> (i * 8)) & 0xFF);

    for (size_t i = 0; i < data.size(); i += 4) {
        blocks.push_back((data[i] & 0xFF) << 24 | (data[i + 1] & 0xFF) << 16 | (data[i + 2] & 0xFF) << 8 | (data[i + 3] & 0xFF));
    }
    return blocks;
}

std::string sha256(const std::string &input) {
    unsigned int h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;

    std::vector<unsigned int> blocks = preprocess(input);

    for (size_t i = 0; i < blocks.size(); i += 16) {
        unsigned int w[64] = {0};
        for (int t = 0; t < 16; t++) w[t] = blocks[i + t];
        for (int t = 16; t < 64; t++) w[t] = sig1(w[t - 2]) + w[t - 7] + sig0(w[t - 15]) + w[t - 16];

        unsigned int a = h0, b = h1, c = h2, d = h3;
        unsigned int e = h4, f = h5, g = h6, h = h7;

        for (int t = 0; t < 64; t++) {
            unsigned int T1 = h + (rotr(6, e) ^ rotr(11, e) ^ rotr(25, e)) + choose(e, f, g) + k[t] + w[t];
            unsigned int T2 = (rotr(2, a) ^ rotr(13, a) ^ rotr(22, a)) + majority(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        h0 += a; h1 += b; h2 += c; h3 += d;
        h4 += e; h5 += f; h6 += g; h7 += h;
    }

    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::setw(8) << h0
       << std::setw(8) << h1 << std::setw(8) << h2 << std::setw(8) << h3
       << std::setw(8) << h4 << std::setw(8) << h5 << std::setw(8) << h6
       << std::setw(8) << h7;
    return os.str();
}

int main() {
    std::string text, target_hash;
    std::cout << "Masukkan TEKS ASLI untuk hashing: ";
    std::getline(std::cin, text);
    
    std::cout << "Masukkan HASH TARGET untuk mencocokkan: ";
    std::getline(std::cin, target_hash);

    std::string generated_hash = sha256(text);

    std::cout << "Hash hasil SHA-256: " << generated_hash << std::endl;

    if (generated_hash == target_hash) {
        std::cout << "Hash cocok dengan target!" << std::endl;
    } else {
        std::cout << "HASH TIDAK COCOK DENGAN TARGET!!!" << std::endl;
    }

    return 0;
}
