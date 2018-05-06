//
// Created by matyas on 05/05/2018.
//

#include <iostream>
#include "utils.h"
#include "CCommandInterpreter.h"

void CCommandInterpreter::GetNext()
{
    std::string command;
    std::string params;

    std::cin >> command;
    getline(std::cin, params);
    trim(params);

    Interpret(command, params);
}

void CCommandInterpreter::Interpret(const std::string & command, const std::string & params)
{
    std::cout << command << std::endl;
    std::cout << params << std::endl;
}