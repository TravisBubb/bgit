#pragma once

#include <cstdlib>
#include "../interfaces/ICommand.hpp"

namespace bgit::commands
{
    class InitCommand : public bgit::interfaces::ICommand
    {
    public:
        InitCommand() {}
        ~InitCommand() {}
        const int execute() const override;
        const int validateOptions(const int, char *[]) const { return EXIT_SUCCESS; };
    };
}