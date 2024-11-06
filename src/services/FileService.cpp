#include "FileService.hpp"
#include <filesystem>
#include <iostream>

namespace bgit::services {
const std::string FileService::GetRelativePathToRoot() {
  std::string path = "";
  std::filesystem::path currentPath = std::filesystem::current_path();

  while (!std::filesystem::exists(currentPath / ".bgit")) {
    if (currentPath == currentPath.root_path()) {
      std::cerr << "Unable to find .bgit directory." << std::endl;
      return path;
    }

    currentPath = currentPath.parent_path();
  }

  path = currentPath.string();
  return path;
}
} // namespace bgit::services
