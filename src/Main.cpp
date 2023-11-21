#include <iostream>
#include "MainUtilities.hpp"
#include "bcrypt.h"
/*
 * This is the entry point to the application.
 * A user will get logged in or create a new application. 
 * A user object will be created for the user. That object will be loaded
 * in with any saved ciphers. The program then interacts with that object
 * to handle user requests.
*/
int main() {
    std::cout << "Greetings To Click" << std::endl;

    // Check for returning user or new user
    int selection = 0;
    while (selection != 1 && selection != 2) {
        std::cout << "Login (1)\nCreate Account(2)\nSelection: ";
        std::cin >> selection;
    }

    // call the correct function for this user.
    User* user = selection == 1 ? Login(false) : NewAccount();
    if (user == nullptr) {
        std::cout << "The program suffered an internal error in account setup\n";
        return 0;
    }

    /*  Main page options
        1. Create a new cipher
        2. See an old cipher
        3. Delete an old cipher
        5. Exit
    */

    while (1) {
        std::cout << "\n~~~~~~~~~~~~~~\n";
        std::cout << "Main Page Options:\nCreate Cipher (1)\nRetrieve Password (2)\n";
        std::cout << "Delete Data (3)\nExit (4)\nSelection: ";
        selection = -1;
        std::cin >> selection;
        std::cout << "\n~~~~~~~~~~~~~~\n";
        switch (selection) {
            case 1:
                user->CreateCipher();
                break;
            case 2:
                user->RetrievePassword();
                break;
            case 3:
                user->DeleteData();
                break;
            case 4:
                user->EncryptFile();
                break;
            case 5:
                user->DecryptFile();
                break;
            case 6:
                // user has opted to exit the program
                return 0;
            default:
                std::cout << "Invalid Selection" << std::endl;
        }
    }
    // This line should never be reached.
    return 0;
}