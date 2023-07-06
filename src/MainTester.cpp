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

    outFile << "Testing creating a new cipher" << std::endl;
    std::string loginName = "Google";
    outFile << "Name the website/login: " << loginName << std::endl;
    std::string ciphertext = p1.xorEncryptPasswordDriver(loginName, "password123", "key");
    outFile << "ciphertext: " << ciphertext << std::endl;
    try {
        ciphertext = p1.xorEncryptPasswordDriver(loginName, "password123", "key");
    } catch (errors_t ex) {
        std::cout << "You already have a login for this account saved.\n";
    }
    p1.xorDecryptPasswordDriver("Goog", "je");

    outFile.close();
    return 0;

}
