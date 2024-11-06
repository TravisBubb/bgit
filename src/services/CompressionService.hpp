#pragma once

#include <string>

namespace bgit::services {
class CompressionService {
public:
  static const std::string compress(const std::string &);
};
} // namespace bgit::services
