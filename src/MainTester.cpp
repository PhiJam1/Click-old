#include <iostream>
#include <fstream>

#include "User.hpp"

/*
    Run this program while in the 'click' directory.
*/
int main() {
    std::ofstream outFile{"DebugLogs/MainTesterDebugLog.txt"};
    if (!outFile.is_open()) {
        std::cout << "MainTester debug log cannot be opened...ABORTING...\n";
        return 0;
    }
    outFile << "In MainTester.cpp\n";

    outFile << "Creating a User object\n";
    User p1("Philip", "James", "PhiJam1", "password");
    outFile << "User was create\n";
    outFile << "Email: " << p1.getEmail();
    outFile << " | First Name: " << p1.getFirstName() << " | Last Name: " << p1.getLastName() << "\n";

    outFile << "Ecrypting a password\n";
    std::string xorTestPassword = "password123";
    std::string xorTestKey = "key";
    outFile << "Given password: " << xorTestPassword << "\n";
    outFile << "Given Key: " << xorTestKey << "\n";
    std::string encryptedPassword = p1.xorEncryptPasswordDriver(xorTestPassword, xorTestKey);
    outFile << "Password: " << encryptedPassword << "\n";

    outFile << "Decrypting that old password\n";
    std::string decryptedPlaintext = p1.xorDecryptPasswordDriver(encryptedPassword, xorTestKey);
    outFile << "Cipher: " << decryptedPlaintext << std::endl;
    

    outFile.close();
    return 0;

}
