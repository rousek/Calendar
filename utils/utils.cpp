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

int requestIntInInterval(int min, int max, bool required)
{
    while(true)
    {
        try
        {
            int number;
            std::string tmp;
            getline(std::cin, tmp);

            if (tmp.empty() && !required)
                throw EmptyLineException();

            number = parseInt(tmp);
            if (number < min || number > max)
                throw 0;

            return number;
        }
        catch (const EmptyLineException & e)
        {
            throw e;
        }
        catch (...)
        {
            std::cout << "Invalid input! Please type in integer in the interval of "
                      << min << " - " << max << "." << std::endl;
        }
    }
}