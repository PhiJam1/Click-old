#include <iostream>
#include "MainUtilities.hpp"
#include "bcrypt.h"
int main() {
    std::cout << "Greetings To Click" << std::endl;


    // std::string hash = bcrypt::generateHash("password");
    // std::cout << hash << std::endl;
    // bool val = bcrypt::validatePassword("passwdord","$2b$10$qs2LdjNEhhKmkrm95cjOzO7sGG07yFqin4JUiB42ngWdscYFn/PbC");
    // if (val) std::cout << "Val\n\n";
    // return 0;

    // Check for returning user or new
    int selection = 0;
    while (selection != 1 && selection != 2) {
        std::cout << "Login (1)\nCreate Account(2)\nSelection: ";
        std::cin >> selection;
    }

    // call the correct function for this user
    if (!(selection == 1 ? Login() : NewAccount())) {
        return 0;
    };
}