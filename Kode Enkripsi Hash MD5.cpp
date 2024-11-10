#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Fungsi rotasi kiri (left rotate)
unsigned int left_rotate(unsigned int x, unsigned int c) {
    return (x << c) | (x >> (32 - c));
}

// Fungsi untuk mengkonversi integer ke string heksadesimal
string to_hex(unsigned int n) {
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << n;
    return ss.str();
}

// Fungsi MD5
void md5(string str) {
    // Inisialisasi variabel
    unsigned int S[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    unsigned int K[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0x00f99a0b, 0x1e2b9b4f, 0x85a1f8a7, 0x461f5e5e, 0x968eaaa1, 0x0d0a4378, 0x01c67c15, 0x7d1a2a6f,
        0x6ad0f5bb, 0x1666e9da, 0xb5f7e7cf, 0x3c8d1610, 0x67921c9e, 0x8c09f1b5, 0x4be2dbf3, 0xb46b7bfe,
        0x4d7ed1b7, 0x7f1b96d0, 0x5d72d0b7, 0x6d6e43be, 0xb2ec82cf, 0xb0d118f2, 0x4346ddc9, 0x8c7b212b,
        0xc63f0b0b, 0xb858b2f2, 0x6ac3d3a3, 0x8da27f82, 0xd74179f2, 0x4cd34f7b, 0x55f1f199, 0x1d182c1e,
        0xf5863a5e, 0xfbe1d2f9, 0x9ffcb6c3, 0x3dd599a7, 0x3da19c8d, 0x3d7cc5d6, 0x8a100694, 0x94ed6d6f
    };

    // Padding (penambahan bit 1 dan 0)
    str += (char)0x80;
    int original_len = str.length() * 8;
    while (str.length() % 64 != 56) {
        str += (char)0x00;
    }

    // Menambahkan panjang pesan dalam 64-bit
    for (int i = 0; i < 8; i++) {
        str += (char)((original_len >> (i * 8)) & 0xFF);
    }

    // Proses MD5
    unsigned int a, b, c, d, f, g, temp;
    for (int i = 0; i < str.length() / 64; i++) {
        unsigned int M[16];
        for (int j = 0; j < 16; j++) {
            M[j] = (unsigned int)((unsigned char)str[i * 64 + j * 4]) |
                   ((unsigned int)((unsigned char)str[i * 64 + j * 4 + 1]) << 8) |
                   ((unsigned int)((unsigned char)str[i * 64 + j * 4 + 2]) << 16) |
                   ((unsigned int)((unsigned char)str[i * 64 + j * 4 + 3]) << 24);
        }

        // Inisialisasi state variabel
        a = S[0];
        b = S[1];
        c = S[2];
        d = S[3];

        for (int j = 0; j < 64; j++) {
            if (j < 16) {
                f = (b & c) | (~b & d);
                g = j;
            } else if (j < 32) {
                f = (d & b) | (~d & c);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = b ^ c ^ d;
                g = (3 * j + 5) % 16;
            } else {
                f = c ^ (b | ~d);
                g = (7 * j) % 16;
            }

            temp = d;
            d = c;
            c = b;
            b = b + left_rotate(a + f + K[j] + M[g], (j < 16 || j >= 32) ? 7 : (j < 32 || j >= 48) ? 11 : 19);
            a = temp;
        }

        // Menambahkan hasil blok ke state
        S[0] += a;
        S[1] += b;
        S[2] += c;
        S[3] += d;
    }

    // Mencetak hasil MD5
    cout << "MD5 Hash: ";
    cout << to_hex(S[0]) << to_hex(S[1]) << to_hex(S[2]) << to_hex(S[3]) << endl;
}

int main() {
    string input;
    cout << "Masukkan string untuk di-hash: ";
    getline(cin, input);

    md5(input);
    return 0;
}
