#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>


/*
    Very basic xor encrytion algorithm. One thing to note is that this program
    will accept a key longer than 1 char. The implementation of that feature here
    makes the cipher text less susceptible to a frequency analysis. Also, the
    program will read and write in parallel, rather than reading an entire file
    into a large buffer, then process it and write it out. This allows it to operate
    on files regardless to size. Space complexity is constant. Time complexity is linear.

    How to use:
    Compile and run the program. It will prompt your for all the info it needs. Put your plaintext
    into your plaintext file. The output will be in a file named 'ciphertext.txt'. The key here is
    similar to a password. The longer and stranger it is, the better.

    Updates:
    Added a more secure encryption and decrytion function. Rather than using a constant key provided
    by the user, this will change the given key after every xor operation. This should make the
    cipher text MUCH less susceptible to a frequency analysis or some brute force attack.

    TODO:
    Change output so it more uniform between different modes/cases
    Allow the user to input the value by which the key changes for advanced modes

*/

void xorDecrypt(std::string ciphertextFileName, std::string key) {
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

void advancedXorDecryption(std::string ciphertextFileName, std::string key) {
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

void advancedXorEncryption(std::string plaintextFileName, std::string key) {
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

void xorEncrypt(std::string plaintextFileName, std::string key) {
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

int main() {

    bool encrypt = false;
    std::cout << "XOR encryptor\n";
    while (1) {
        std::cout << "Encrypt (1)\nDecrypt(2)\nAdvanced Encryption (3)\nAdvanced Decryption (4)\n";
        int optionTemp = 0;
        std::cin >> optionTemp;
        if (optionTemp == 1) {
            std::string plaintextFileName;
            std::string key;
            std::cout << "Please enter plaintext file name: ";
            std::cin >> plaintextFileName;
            std::cout << "Please enter a key: ";
            std::cin >> key;
            xorEncrypt(plaintextFileName, key);
            break;
        }
        if (optionTemp == 2) {
            std::string ciphertextFileName;
            std::string key;
            std::cout << "Please enter ciphertext file name: ";
            std::cin >> ciphertextFileName;
            std::cout << "Please enter your key: ";
            std::cin >> key;
            xorDecrypt(ciphertextFileName, key);
            break;
        }
        if (optionTemp == 3) {
            std::string plaintextFileName;
            std::string key;
            std::cout << "Please enter plaintext file name: ";
            std::cin >> plaintextFileName;
            std::cout << "Please enter a key: ";
            std::cin >> key;
            advancedXorEncryption(plaintextFileName, key);
            break;
        }
        if (optionTemp == 4) {
            std::string ciphertextFileName;
            std::string key;
            std::cout << "Please enter ciphertext file name: ";
            std::cin >> ciphertextFileName;
            std::cout << "Please enter your key: ";
            std::cin >> key;
            advancedXorDecryption(ciphertextFileName, key);
            break;
        }
        else {
            std::cout << "Invalid selection\n";
        }
    }
    return 0;
}
