#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <fstream>
#include <ios>
#include <bits/stdc++.h>

#include "User.hpp"
#include "bcrypt.h"
#include "MainUtilities.hpp"

User* Login(bool new_user) {
    // user information
    std::string first_name = " ";
    std::string last_name = " ";
    std::string email = " ";
    std::string password = " ";

    while (1) {
        std::cout << "Enter email: ";
        std::cin >> email;

        // make email fully lower case
        std::transform(email.begin(), email.end(), email.begin(), [](unsigned char c){ return std::tolower(c); });
        
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
                    // construct a new user object and send back the address
                    User* user = nullptr;
                    if (new_user) {
                        user = new User(first_name, last_name, email, password, salt);
                        user->SaveUserData();
                    } else {
                        user = new User(email, password);
                    }
                    return user;
                }
            }
        }
        std::cout << "Invalid Login\nTry Again (1)\nCreate Account (2)\nSelection: ";
        int selection;
        std::cin >> selection;
        if (selection == 2) {
            return NewAccount();
        }
    }
    return nullptr;
}

User* NewAccount() {
    // user information
    std::cout << "Creating a new account\n";
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
                return Login(false);
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
        return nullptr;
    }
    ofs << "--\n" <<
    first_name << "\n" << last_name << "\n" 
    << hash << "\n" << salt << "\n" << email << "\n";
    ofs.close();
    // redirect to the login page
    std::cout << "You'll be redirected to the login page\n";
    return Login(true);
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
// note, these random  numbers aren't secure, but that's fine because
// we can still ensure security if the salt is breached. Also, we store
// the salt as plaintext next to the password hash, so its not really a secret.
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
