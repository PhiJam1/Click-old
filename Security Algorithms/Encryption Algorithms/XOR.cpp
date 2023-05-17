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
    on large files.

    How to use:
    Compile and run the program. It will prompt your for all the info it needs.
    If you use the same set of 2 files for testing, be aware that this program will
    clear both. Also, the key is the value that will be xored with the data. It must
    be shorter than the length of the data.

    TODO:
    Clean up code
    add better/more comments
    Account for non 'round' keys
    check and handle keys larger than a file
    add a message that an operation has finished
    testing
*/

void xorDecrypt(std::string ciphertextFileName, std::string key) {
    //open encrypted file for reading
    std::ifstream cipherFile;
    cipherFile.open(ciphertextFileName);
    if (cipherFile.fail()) {
        //file could not be opened
        std::cout << "Ciphertext file could not be opened\n";
        return;
    }
    std::ofstream plainFile;
    plainFile.open("plaintext.txt");
    if (plainFile.fail()) {
        std::cout << "Plaintext file could not be opened\n";
        return;
    }
    std::string buff = "";
    for (int i = 0; cipherFile >> buff; i++) {
        char c = key[i % key.length()];
        c ^= stoi(buff);
        plainFile << c;
    }
    plainFile.close();
    cipherFile.close();
}

void xorEncrypt(std::string plaintextFileName, std::string key) {
    //open plaintext file
    std::ifstream plaintextFP;
    plaintextFP.open(plaintextFileName);
    if (plaintextFP.fail()) {
        //we could not open the plaintext file
        std::cout << "Plaintext file could not be opened/located\n";
        return;
    }

    //open the ciphertext file
    std::ofstream ciphertextFP;
    ciphertextFP.open("ciphertext.txt");
    if (ciphertextFP.fail()) {
        std::cout << "Error trying to write cipher text\n";
        plaintextFP.close();
        return;
    }

    std::cout << "Encrypting ... data will be written to a file named 'ciphertext.txt' when finished" << std::endl;
    char c;
    char buff[key.length()];
    int i = 0;
    while (plaintextFP.get(c)) {
        buff[i] = c;
        if (i == key.length() - 1) {
            //buffer is full and can be proccessed
            for (int j = 0; j < key.length(); j++) {
                int b = buff[j];
                int k = key.at(j);
                int data = b ^ k;
                std::cout << k << " ";
                ciphertextFP << data << " ";
            }
            i = 0;
            continue;
        }
        i++;
    }
    ciphertextFP.close();
    plaintextFP.close();

}

int main() {

    bool encrypt = false;
    std::cout << "Basic XOR encryption\n";
    while (1) {
        std::cout << "Encrypt or Decrypt (1 or 2): ";
        int optionTemp = 0;
        std::cin >> optionTemp;
        encrypt = (optionTemp == 1) ? true : false;
        if (!(optionTemp == 1 || optionTemp == 2)) {
            std::cout << ":| ... dude, try again\n";
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
        if (key.length() <= 1) {
            std::cout << "Consider a stronger key next time\n";
        }
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
