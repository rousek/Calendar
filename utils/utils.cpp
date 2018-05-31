//
// Created by matyas on 05/06/2018.
//

#include <iostream>
#include "utils.h"

bool requestConfirm(const std::string & msg)
{
    std::cout << msg << " (Y/n)" << std::endl;

    while(true)
    {
        char answer;

        if (!(std::cin >> answer) || (answer != 'Y' && answer != 'n'))
        {
            std::cout << "Invalid input! Please only type in Y or n." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (answer == 'Y')
            return true;
        if (answer == 'n')
            return false;

    }
}