#include <iostream>
#include <string>
using namespace std;

// Fungsi untuk mengenkripsi pesan menggunakan XOR Cipher
string xorEncrypt(const string &input, char key) {
    string result = input;
    for (size_t i = 0; i < input.size(); ++i) {
        result[i] = input[i] ^ key;  // Operasi XOR antara karakter dan key
    }
    return result;
}

int main() {
    string text;
    char key;
    
    // Input pesan yang akan dienkripsi
    cout << "Masukkan pesan yang akan dienkripsi: ";
    getline(cin, text);
    
    // Input kunci untuk XOR
    cout << "Masukkan kunci (1 karakter): ";
    cin >> key;
    
    // Enkripsi pesan
    string encryptedText = xorEncrypt(text, key);
    cout << "Pesan terenkripsi: " << encryptedText << endl;
    
    return 0;
}
