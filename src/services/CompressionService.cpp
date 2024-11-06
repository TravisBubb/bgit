#include "CompressionService.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <zlib.h>

namespace bgit::services {
const std::string CompressionService::compress(const std::string &content) {
  z_stream zs;
  memset(&zs, 0, sizeof(zs));

  if (deflateInit(&zs, Z_DEFAULT_COMPRESSION) != Z_OK) {
    std::cerr << "Error initializing zlib\n";
    throw new std::runtime_error("zlib deflateInit failed");
  }

  zs.next_in = (Bytef *)content.data();
  zs.avail_in = content.size();

  std::string compressed;
  int ret;
  const int CHUNK_SIZE = 1024;
  char outputBuffer[CHUNK_SIZE];
  do {
    zs.next_out = reinterpret_cast<Bytef *>(outputBuffer);
    zs.avail_out = sizeof(outputBuffer);

    ret = deflate(&zs, Z_FINISH);
    if (ret == Z_STREAM_ERROR) {
      std::cerr << "Error deflating content\n";
      throw new std::runtime_error("zlib deflate failed");
    }

    compressed.append(outputBuffer,
                      zs.next_out - reinterpret_cast<Bytef *>(outputBuffer));
  } while (ret != Z_STREAM_END);

  deflateEnd(&zs);
  compressed.resize(zs.total_out);

  return compressed;
}
} // namespace bgit::services
