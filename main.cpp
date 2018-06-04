#include "UI/CCommandInterpreter.h"

int main(int argc, char ** argv)
{
    CCommandInterpreter calendar;

    if (argc == 2)
        calendar.Import({std::string(argv[1])});
    else if (argc != 1)
    {
        std::cout << "Usage: " << std::endl
                  << "\"calendar\"" << std::endl
                  << "\"calendar file_name\"" << std::endl;
        return 1;
    }

    calendar.Run();
    return 0;
}