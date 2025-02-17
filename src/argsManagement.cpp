#include "../include/errorCode.hpp"
#include "../include/proto.hpp"

int checkArgsValidity(int argc, char **argv)
{
    if (argc == 2)
    {
        return (EXIT_SUCCESS);
    }
    else if (argc == 3)
    {
        if (strcmp(argv[2], "small") == 0)
            return (1);
        else if (strcmp(argv[2], "medium") == 0)
            return (EXIT_SUCCESS);
        else if (strcmp(argv[2], "big") == 0)
            return (2);
        else
            return (ERROR_CODE);
    }
    else
        return (ERROR_CODE);
}