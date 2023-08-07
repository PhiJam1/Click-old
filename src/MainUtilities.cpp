#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "bcrypt.h"
#include "MainUtilities.hpp"

bool Login() {
    return false;
}

bool NewAccount() {
    // user information
    std::string first_name = " ";
    std::string last_name = " ";
    std::string email = " ";
    std::string password = " ";
    std::string salt = " ";
    std::string hash = " ";

    // Get first name, last name
    while (first_name == " ") {
        std::cout << "Enter First Name: ";
        std::cin >> first_name;
    }
    while (last_name == " ") {
        std::cout << "Enter Last Name: ";
        std::cin >> last_name;
    }

    // Get email. Ensure it has not been used before
    while (email == " ") {
        std::cout << "Enter a email: ";
        std::cin >> email;
        if (EmailInUse(email)) {
            int selection = 0;
            while (selection != 1 && selection != 2) {
                std::cout << "Email is already in use.\n Login Page (1)\nUse Different Email (2)";
                std::cin >> selection;
            }
            if (selection == 1) {
                return Login();
            } else {
                email = " ";
            }
        }
    }
    // Get a password and assign a salt
    while (password == " ") {
        std::cout << "Enter password: ";
        std::cin >> password;
        // EnforcePasswordRules() - do this later
        salt = GenSalt();
        hash = bcrypt::generateHash(password + salt);
    }

    // Save the hash, salt, and other user data
    std::ofstream ofs{CRED_FILENAME};
    if (!ofs.is_open()) return false;
    ofs << "--\n" << email << "\n" << salt << "\n" << hash << "\n";
    ofs.close();
    // redirect to the login page
    return true;
    return Login();
}

bool EmailInUse(std::string email) {
    return false;
}

std::string GenSalt() {
    srand((int) time(0));
    int len = (rand() % 10) + 5; // length will vary from 5 to 14 inclusive
    std::string salt = "";
    for (int i = 0; i < len; i++) {
        char r = (rand() % 94) + 33; // from 33 to 126 inclusive
        salt += (char) r;
    }
    return salt;
}