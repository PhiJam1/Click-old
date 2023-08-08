#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <fstream>
#include <ios>
#include <bits/stdc++.h>
#include "bcrypt.h"
#include "MainUtilities.hpp"

bool Login() {
    // user information
    std::string first_name = " ";
    std::string last_name = " ";
    std::string email = " ";
    std::string password = " ";

    while (1) {
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter password: ";
        std::cin >> password;
        
        // get the password hash for this email
        std::ifstream ifs{CRED_FILENAME};
        std::string buff;
        std::string tmp_email = "";
        std::string hash;
        std::string salt;
        while (ifs.good()) {
            ifs >> buff; // the --
            ifs >> first_name;
            ifs >> last_name;
            ifs >> hash;
            ifs >> salt;
            ifs >> tmp_email;
            if (tmp_email == email) {
                // check the passwords
                if (bcrypt::validatePassword(password + salt, hash)) {
                    std::cout << "Welcome " + first_name << std::endl;
                    return true;
                }
            }
        }
        std::cout << "Invalid\n";
    }
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
        // make email fully lower case
        std::transform(email.begin(), email.end(), email.begin(), [](unsigned char c){ return std::tolower(c); });
        if (EmailInUse(email)) {
            int selection = 0;
            while (selection != 1 && selection != 2) {
                std::cout << "Email is already in use.\nLogin Page (1)\nUse Different Email (2)\nSelection: ";
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
    while (password == " " || !ValidPassword(password)) {
        std::cout << "Enter password: ";
        std::cin >> password;
    }
    // EnforcePasswordRules() - do this later
    salt = GenSalt();
    hash = bcrypt::generateHash(password + salt);

    // Save the hash, falsesalt, and other user data
    std::ofstream ofs(CRED_FILENAME, std::ios::out | std::ios::app);
    if (!ofs.is_open()) {
        return false;
    }
    ofs << "--\n" <<
    first_name << "\n" << last_name << "\n" 
    << hash << "\n" << salt << "\n" << email << "\n";
    ofs.close();
    // redirect to the login page
    return Login();
}

bool ValidPassword(std::string password) {
    // check for length
    if (password.size() < 5 || password.size() > 15) {
        std::cout << "Password must be between 5 and 15 characters long\n";
        return false;
    }
    bool lower_case = false;
    bool upper_case = false;
    bool num = false;
    bool letter = false;
    bool special_char = false;
    for (int i = 0; i < password.size(); i++) {
        char let = password.at(i);
        if (tolower(let) == let) lower_case = true;
        if (toupper(let) == let) upper_case = true;
        if (isdigit(let)) num = true;
        if (isalpha(let)) letter = true;
        if (!isalnum(let)) special_char = true;
    }
    if (!lower_case) {
        std::cout << "Password must contian at least one lower case letter\n";
        return false;
    } else if (!upper_case) {
        std::cout << "Password must contian at least one upper case letter\n";
        return false;
    } else if (!num) {
        std::cout << "Password must contian at least one number\n";
        return false;
    } else if (!letter) {
        std::cout << "Password must contian at least one letter\n";
        return false;
    } else if (!special_char) {
        std::cout << "Password must contian at least one special character\n";
        return false;
    } else {
        return true;
    }
}

bool EmailInUse(std::string email) {
    std::ifstream ifs{CRED_FILENAME};
    std::string buff;
    std::string curr_email;
    while (ifs.good()) {
        ifs >> buff; // get the --
        for (int i = 0; i < 4 && ifs.good(); i++) 
            ifs >> buff;
        ifs >> curr_email; // email
        if (email == curr_email) {
            return true;
        }
    }
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