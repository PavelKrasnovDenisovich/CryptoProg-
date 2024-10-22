#include <string>
#include <iostream>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/cbcmac.h>

using namespace std;
using namespace CryptoPP;

void encrypt() {
    string str;
    string strs = "";
    string file;
    cout << "Введите имя файла, откуда считать текст:";
    cin >> file;
    ifstream fs (file);
    char ch;
    while (fs.get(ch)) {
        strs.push_back(ch);
    }
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string plaintext = strs;
    string ciphertext;
    cout << "Plain Text: " << plaintext << std::endl;
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length());
    stfEncryptor.MessageEnd();
    cout << "Выберете файл куда записать: ";
    string imp, file2;
    cin >> file2;
    cout << "Cipper Text: " << ciphertext << std::endl;
    ofstream fs2 (file2);
    for (int i = 0; i < ciphertext.size(); i++) {
        fs2 << ciphertext[i];
    }
}

void decrypt() {
    string str;
    string strs = "";
    string file;
    cout << "Введите имя файла, откуда считать текст:";
    cin >> file;
    ifstream fs (file);
    char ch;
    while (fs.get(ch)) {
        strs.push_back(ch);
    }
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string plaintext = strs;
    string decryptedtext;
    cout << "Plain Text: " << plaintext << std::endl;
    string imp, file2;
    cout << "Выберете файл куда записать: ";
    cin >> file2;
    ofstream fs2 (file2);
    ifstream fs3 (file2);
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
    stfDecryptor.MessageEnd();
    cout << decryptedtext << endl;
    fs2 << decryptedtext;
}

int main(){
    ifstream fs;
    ofstream fs2;
    ifstream fs3;
    string str;
    string strs = "";
    string file;
    int k;
            do {
                cout << "\nВедите 1, если шифровать или 2, если расшифровать или 0, чтобы выйти:";
                cin >> k;
                if (k == 1) {
                    encrypt();
                }
                else  if (k == 2) {
                    decrypt();
                }
            } while (k != 0);
    return 0;
}
