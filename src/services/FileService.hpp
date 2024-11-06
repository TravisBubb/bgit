#pragma once

#include <string>

namespace bgit::services {
class FileService {
public:
  static const std::string GetRelativePathToRoot();
};
} // namespace bgit::services
