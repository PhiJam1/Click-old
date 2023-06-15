#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <iostream>
#include <vector>

#define MAX_LOGIN_NAME_SIZE 50 //Please change as needed
#define NUM_CIPHERS 4 //Please change as needed

enum CipherTypes
{
    XOR,
    BLOWFISH,
    AES,
    SHA
};

class Ciphers {

    private:
        std::string loginName;  // Like a company name
        CipherTypes cipherName; // Maybe we change this to an enum?
        std::string key;
        int numPaddedZeros; // Just put in -1 if not applicable for this cipher

    public:
        Cipher(std::string loginName, CipherTypes cipherName, std::string key, int zeros);
        std::string getLoginName();
        CipherTypes getCipherName();
        std::string getKey();
        int getNumPaddedZeros();
        // Setters
        bool setLoginName(std::string newLoginName);
        bool setCipherName(CipherTypes newCipherName);
        bool setKey(std::string newKey);
}

#endif