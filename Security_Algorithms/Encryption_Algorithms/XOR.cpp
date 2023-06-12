#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

#include "XOR.h"
/*
    Very basic xor encrytion algorithm. One thing to note is that this program
    will accept a key longer than 1 char. The implementation of that feature here
    makes the cipher text less susceptible to a frequency analysis. Also, the
    program will read and write in parallel, rather than reading an entire file
    into a large buffer, then process it and write it out. This allows it to operate
    on files regardless to size. Space complexity is constant. Time complexity is linear.
    Added a more secure encryption and decrytion function. Rather than using a constant key provided
    by the user, this will change the given key after every xor operation. This should make the
    cipher text MUCH less susceptible to a frequency analysis or some brute force attack.

    How to use:
    Compile and run the program. It will prompt your for all the info it needs. Put your plaintext
    into your plaintext file. The output will be in a file named 'ciphertext.txt'. The key here is
    similar to a password. The longer and stranger it is, the better.
    - This is outdated. The driver of this code with be from the user class, which will be driven by
    the main.cpp file.

    Updates:
    Currenlty working to adapted the code to work better with the rest of the project structure. Rather than
    read and write to files, it will be recieving all that info from the user class and returning back to User.cpp.
    - Philip James 06/11/2023

    TODO:
    Alter read and write from files to interact with user class.
    Allow the user to input the value by which the key changes for advanced modes

    TEST THE SIZEOF STATEMENTS

*/


/* Password functions */

std::string xorEncryptPassword(std::string plaintext, std::string key) {
    char c;
    std::string ciphertext = "";
    //Xors each character in plaintext with a character in key
    for (int i = 0; i < plaintext.size(); i++) {
        c = plaintext[i];
        ciphertext += (c ^ key.at(i % key.length())) + " ";
    } 
    return ciphertext;
}

std::string xorDecryptPassword(int ciphertext[], std::string key) {

    std::string plaintext = "";
    for (int i = 0; sizeof(ciphertext) / sizeof(ciphertext[0]); i++) {
        char c = key[i % key.length()];
        //stoi() converts the string to an ascii integer
        c ^= ciphertext[i];
        plaintext += c;
    }
    return plaintext;
}

std::string advancedXorDecryptionPassword(int ciphertext[], std::string key) {
    std::string plaintext = "";
    for (int i = 0; i < sizeof(ciphertext) / sizeof(ciphertext[0]); i++) {

        char c = key[i % key.length()];
        c ^= ciphertext[i];
        plaintext += c;
        key[i % key.length()] = ((key[i % key.length()] + 1) % 127) + 1;
    }
    return plaintext;
}

std::string advancedXorEncryptionPassword(std::string plaintext, std::string key) {
    char c;
    std::string ciphertext = "";

    //Xors each character in plaintext with a character in key
    for (int i = 0; i < plaintext.size(); i++) {
        ciphertext += (c ^ key.at(i % key.length())) + " ";
        key[i % key.length()] = ((key[i % key.length()] + 1) % 127) + 1;
    }
    return ciphertext;
}





/*
    This function will manage all password xor function. 
    text: This can be plaintext, ciphertext, or a file path
    cipher text: This is for decryption. It will be the integers used as cipher text
    key: The key for this encryption
    adv: true if this is an advanced encryption
    encrypt: true if this is to encrypt given data
*/

std::string xorManagerPassword(std::string text, int ciphertext[], std::string key, bool adv, bool encrypt) {
    if (encrypt) {
        if (adv) {
            return advancedXorEncryptionPassword(text, key);
        } else {
            return xorEncryptPassword(text, key);
        }
    } else {
        if (adv) {
            return advancedXorDecryptionPassword(ciphertext, key);
        } else {
            return xorDecryptPassword(ciphertext, key);
        }
    }
}

std::string xorManagerFile() {
    return "";
    //todo
}


/* File functions */


void xorDecryptFile(std::string ciphertextFileName, std::string key) {
    //open encrypted file for reading
    std::ifstream cipherFile;
    cipherFile.open(ciphertextFileName);

    if (cipherFile.fail()) {
        //file could not be opened for reading
        std::cout << "Ciphertext file could not be opened\n";
        return;
    }
    
    std::ofstream plainFile;
    plainFile.open("plaintext.txt");
    if (plainFile.fail()) {
        //File could not be opened for writing
        std::cout << "Plaintext file could not be opened\n";
        return;
    }

    std::cout << "Decrypting data... " << std::endl;
    std::string buff = "";
    for (int i = 0; cipherFile >> buff; i++) {
        char c = key[i % key.length()];
        //stoi() converts the string to an ascii integer
        c ^= stoi(buff);
        plainFile << c;
    }

    //close files
    plainFile.close();
    cipherFile.close();

    std::cout << "Data have been saved to 'plaintext.txt'" << std::endl;
}

void advancedXorDecryptionFile(std::string ciphertextFileName, std::string key) {
    //open encrypted file for reading
    std::ifstream cipherFile;
    cipherFile.open(ciphertextFileName);

    if (cipherFile.fail()) {
        //file could not be opened for reading
        std::cout << "Ciphertext file could not be opened\n";
        return;
    }
    
    std::ofstream plainFile;
    plainFile.open("plaintext.txt");
    if (plainFile.fail()) {
        //File could not be opened for writing
        std::cout << "Plaintext file could not be opened\n";
        return;
    }

    std::cout << "Decrypting data... " << std::endl;
    std::string buff = "";
    for (int i = 0; cipherFile >> buff; i++) {
        char c = key[i % key.length()];
        //stoi() converts the string to an ascii integer
        c ^= stoi(buff);
        plainFile << c;
        key[i % key.length()] = ((key[i % key.length()] + 1) % 127) + 1;
    }

    //close files
    plainFile.close();
    cipherFile.close();

    std::cout << "Data have been saved to 'plaintext.txt'" << std::endl;
}

void advancedXorEncryptionFile(std::string plaintextFileName, std::string key) {
    //open plaintext file
    std::ifstream plaintextFile;
    plaintextFile.open(plaintextFileName);

    if (!plaintextFile.is_open()) {
        std::cout << "Plaintext file could not be opened\n";
        return;
    }

    //Open cipher text file
    std::ofstream ciphertextFile;
    ciphertextFile.open("ciphertext.txt");
    
    if (!ciphertextFile.is_open()) {
        std::cout << "Error writing data\n";
    }

    std::cout << "Encrypting ..." << std::endl;
    char c;

    //Xors each character in plaintext with a character in key
    for (int i = 0; plaintextFile.get(c); i++) {
        ciphertextFile << (c ^ key.at(i % key.length())) << " ";
        int x = ((key[i % key.length()] + 1) % 127) + 1;
        key[i % key.length()] = ((key[i % key.length()] + 1) % 127) + 1;
        std::cout << key << " - > " << x << std::endl;
    }

    //close files
    ciphertextFile.close();
    plaintextFile.close();

    std::cout << "Data have been saved to 'ciphertext.txt'" << std::endl;

}

void xorEncryptFile(std::string plaintextFileName, std::string key) {
    
    //open plaintext file
    std::ifstream plaintextFP;
    plaintextFP.open(plaintextFileName);
    if (plaintextFP.fail()) {
        //we could not open the plaintext file for reading
        std::cout << "Plaintext file could not be opened\n";
        return;
    }

    //open the ciphertext file
    std::ofstream ciphertextFP;
    ciphertextFP.open("ciphertext.txt");
    if (ciphertextFP.fail()) {
        //we could not open the cipher text file for writing
        std::cout << "Cipher text file could not be opened\n";
        plaintextFP.close();
        return;
    }

    std::cout << "Encrypting ..." << std::endl;
    char c;

    //Xors each character in plaintext with a character in key
    for (int i = 0; plaintextFP.get(c); i++) {
        ciphertextFP << (c ^ key.at(i % key.length())) << " ";
    } 
    

    //close files
    ciphertextFP.close();
    plaintextFP.close();

    std::cout << "Data have been saved to 'ciphertext.txt'" << std::endl;
}
