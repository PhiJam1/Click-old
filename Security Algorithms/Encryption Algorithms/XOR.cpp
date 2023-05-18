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

    TODO:
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
        std::cout << "Encrypt or Decrypt (1 or 2): ";
        int optionTemp = 0;
        std::cin >> optionTemp;
        encrypt = (optionTemp == 1) ? true : false;
        if (!(optionTemp == 1 || optionTemp == 2)) {
            std::cout << "Invalid Option\n";
        } else {
            break;
        }
    }

    if (encrypt) {
        std::string plaintextFileName;
        std::string key;
        std::cout << "Please enter plaintext file name: ";
        std::cin >> plaintextFileName;
        std::cout << "Please enter a key: ";
        std::cin >> key;
        xorEncrypt(plaintextFileName, key);
    } else {
        std::string ciphertextFileName;
        std::string key;
        std::cout << "Please enter ciphertext file name: ";
        std::cin >> ciphertextFileName;
        std::cout << "Please enter your key: ";
        std::cin >> key;
        xorDecrypt(ciphertextFileName, key);
    }
    return 0;
}
