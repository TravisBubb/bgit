#include "HashObjectCommand.hpp"

#include <iostream>

namespace bgit::commands
{
    const int HashObjectCommand::execute() const
    {
        return EXIT_SUCCESS;
    }

    const int HashObjectCommand::validateOptions(const int, char *[]) const
    {
        return EXIT_SUCCESS;
    }
}