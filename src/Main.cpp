#include <iostream>
#include "MainUtilities.hpp"

int main() {
    std::cout << "Greetings To Click" << std::endl;

    // Check for returning user or new
    int selection = 0;
    while (selection != 1 && selection != 2) {
        std::cout << "Select\nLogin (1)\nCreate Account(2)\n";
        std::cin >> selection;
    }

    // call the correct function for this user
    if (!(selection == 1 ? Login() : NewAccount())) {
        return 1;
    };
}