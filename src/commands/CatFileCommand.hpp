#pragma once

#include <cstdlib>
#include "../interfaces/ICommand.hpp"

namespace bgit::commands
{
    class CatFileCommand : public bgit::interfaces::ICommand
    {
    public:
        CatFileCommand() {}
        ~CatFileCommand() {}
        const bool execute() const override;
        const bool validateOptions(const int, char*[]) override { return true; };
    };
}