#include <string>
#include "CommandFactory.hpp"
#include "Constants.hpp"
#include "commands/InitCommand.hpp"
#include "commands/CatFileCommand.hpp"
#include "commands/HashObjectCommand.hpp"

namespace bgit
{
    std::unique_ptr<bgit::interfaces::ICommand> CommandFactory::Create(std::string type)
    {
        if (type == INIT)
            return std::make_unique<bgit::commands::InitCommand>();
        else if (type == CAT_FILE)
            return std::make_unique<bgit::commands::CatFileCommand>();
        else if (type == HASH_OBJECT)
            return std::make_unique<bgit::commands::HashObjectCommand>();

        return nullptr;
    }
}