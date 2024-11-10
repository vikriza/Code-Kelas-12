#include <iostream>
#include <string>
using namespace std;

// Fungsi enkripsi Vigenère Cipher
string vigenereEncrypt(const string &text, const string &key) {
    string result = text;
    int keyIndex = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            int shift = tolower(key[keyIndex % key.size()]) - 'a';
            result[i] = (text[i] - base + shift) % 26 + base;
            keyIndex++;
        }
    }
    return result;
}

int main() {
    string text, key;

    // Input pesan dan kunci
    cout << "Masukkan teks untuk dienkripsi: ";
    getline(cin, text);
    cout << "Masukkan kata kunci: ";
    getline(cin, key);

    // Enkripsi pesan
    string encryptedText = vigenereEncrypt(text, key);
    cout << "Teks terenkripsi: " << encryptedText << endl;

    return 0;
}
