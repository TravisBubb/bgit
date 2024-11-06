#pragma once

#include "interfaces/ICommand.hpp"
#include <memory>

namespace bgit {
class CommandFactory {
public:
  CommandFactory() {}
  ~CommandFactory() {}
  std::unique_ptr<bgit::interfaces::ICommand> Create(const std::string &);
};
} // namespace bgit
