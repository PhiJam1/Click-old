#include <iostream>
#include "MainUtilities.hpp"
#include "bcrypt.h"
/*

todo: default the filename constructor of the user class to handle the case of no saved data
todo: login page does not make all emails entered lowercase\

*/
int main() {
    std::cout << "Greetings To Click" << std::endl;

    // Check for returning user or new
    int selection = 0;
    while (selection != 1 && selection != 2) {
        std::cout << "Login (1)\nCreate Account(2)\nSelection: ";
        std::cin >> selection;
    }

    // call the correct function for this user
    User* user = selection == 1 ? Login(false) : NewAccount();
    if (user == nullptr) {
        return 0;
    }

    /*  Main page options
        1. Create a new cipher
        2. See an old cipher
        3. Delete an old cipher
        5. Exit
    */

   while (1) {
        std::cout << "Main Page Options:\nCreate Cipher (1)\nRetrieve Password (2)\n";
        std::cout << "Delete Data (3)\nExit (4)\nSelection: ";
        selection = -1;
        std::cin >> selection;
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
                return 0;
            default:
                std::cout << "Invalid Selection" << std::endl;
        }
   }

}