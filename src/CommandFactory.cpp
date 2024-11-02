#include <string>
#include "CommandFactory.hpp"
#include "Constants.hpp"
#include "commands/Init.hpp"

namespace bgit
{

    std::unique_ptr<bgit::interfaces::ICommand> CommandFactory::Create(std::string type)
    {
        if (type == INIT)
        {
            return std::make_unique<bgit::commands::Init>();
        }

        return nullptr;
    }
}