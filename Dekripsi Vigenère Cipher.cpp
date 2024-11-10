#include <iostream>
#include <string>
using namespace std;

// Fungsi dekripsi Vigenère Cipher
string vigenereDecrypt(const string &text, const string &key) {
    string result = text;
    int keyIndex = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            int shift = tolower(key[keyIndex % key.size()]) - 'a';
            result[i] = (text[i] - base - shift + 26) % 26 + base;
            keyIndex++;
        }
    }
    return result;
}

int main() {
    string text, key;

    // Input pesan yang dienkripsi dan kata kunci
    cout << "Masukkan teks yang telah dienkripsi: ";
    getline(cin, text);
    cout << "Masukkan kata kunci: ";
    getline(cin, key);

    // Dekripsi pesan
    string decryptedText = vigenereDecrypt(text, key);
    cout << "Teks yang didekripsi: " << decryptedText << endl;

    return 0;
}
