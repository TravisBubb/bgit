#include "CommandFactory.hpp"
#include "Constants.hpp"
#include "commands/CatFileCommand.hpp"
#include "commands/HashObjectCommand.hpp"
#include "commands/InitCommand.hpp"
#include <string>

namespace bgit {
std::unique_ptr<bgit::interfaces::ICommand>
CommandFactory::Create(const std::string &type) {
  if (type == INIT)
    return std::make_unique<bgit::commands::InitCommand>();
  else if (type == CAT_FILE)
    return std::make_unique<bgit::commands::CatFileCommand>();
  else if (type == HASH_OBJECT)
    return std::make_unique<bgit::commands::HashObjectCommand>();

  return nullptr;
}
} // namespace bgit
