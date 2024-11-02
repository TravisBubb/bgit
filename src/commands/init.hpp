#pragma once

#include "../interfaces/ICommand.hpp"

namespace bgit::commands
{
    class Init : public bgit::interfaces::ICommand
    {
    public:
        Init() {}
        ~Init() {}
        int execute() const override;
    };
}