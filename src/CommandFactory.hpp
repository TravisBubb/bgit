#pragma once

#include <memory>
#include "interfaces/ICommand.hpp"

namespace bgit
{
    class CommandFactory
    {
    public:
        CommandFactory() {}
        ~CommandFactory() {}
        std::unique_ptr<bgit::interfaces::ICommand> Create(std::string type);
    };
}
