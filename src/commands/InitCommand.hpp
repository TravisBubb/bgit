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
        const bool execute() const override;
        const bool validateOptions(const int, char *[]) override { return true; };
    };
}