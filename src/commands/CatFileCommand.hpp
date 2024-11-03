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
        const int execute() const override;
        const int validateOptions(const int, char*[]) const override { return EXIT_SUCCESS; };
    };
}