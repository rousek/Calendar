#include "UI/CCommandInterpreter.h"

int main(int argc, char ** argv)
{
    CCommandInterpreter calendar;

    switch (argc)
    {
        case 1:
            calendar.Run();
            break;
        case 2:
            calendar.Run(argv[1]);
            break;
        default:
            std::cout << "Usage: " << std::endl
                      << "\"calendar\"" << std::endl
                      << "\"calendar file_name\"" << std::endl;
            return 1;
    }

    return 0;
}