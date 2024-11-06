#include "HashObjectCommand.hpp"
#include "../Constants.hpp"
#include "../services/CompressionService.hpp"
#include "../services/FileService.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>
#include <zlib.h>

namespace bgit::commands {
static const bool UsageError();

const bool HashObjectCommand::execute() const {
  std::ifstream file(this->objectPath, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << this->objectPath << '\n';
    return false;
  }

  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  if (!ctx) {
    std::cerr << "Error creating EVP_MD_CTX\n";
    return false;
  }

  if (EVP_DigestInit_ex(ctx, EVP_sha1(), nullptr) != 1) {
    std::cerr << "Error initializing digest\n";
    EVP_MD_CTX_free(ctx);
    return false;
  }

  std::uintmax_t inputFileSize = std::filesystem::file_size(this->objectPath);
  std::stringstream inputStream;
  inputStream << "blob " << inputFileSize << '\0' << file.rdbuf();

  file.close();

  inputStream.seekg(0, std::ios::end);
  const int inputStringSize = inputStream.tellg();
  inputStream.seekg(0, std::ios::end);
  std::string contentWithHeader = inputStream.str();
  const char *inputString = contentWithHeader.c_str();

  if (EVP_DigestUpdate(ctx, inputString, inputStringSize) != 1) {
    std::cerr << "Error updating digest\n";
    EVP_MD_CTX_free(ctx);
    return false;
  }

  unsigned char hash[SHA_DIGEST_LENGTH];
  unsigned int hashLength;
  if (EVP_DigestFinal_ex(ctx, hash, &hashLength) != 1) {
    std::cerr << "Error finalizing digest\n";
    EVP_MD_CTX_free(ctx);
    return false;
  }

  EVP_MD_CTX_free(ctx);

  std::stringstream hashStream;

  for (unsigned int i = 0; i < hashLength; ++i) {
    hashStream << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(hash[i]);
  }

  std::string hashString = hashStream.str();
  std::cout << hashString << '\n';

  if (!this->writeObject)
    return true;

  std::string root = services::FileService::GetRelativePathToRoot();
  std::string prefix = hashString.substr(0, 2);
  hashString.erase(0, 2);
  std::string path = root + "/.bgit/objects/" + prefix;
  std::filesystem::create_directory(path);

  path += "/" + hashString;

  std::ofstream outputFile(path, std::ios::binary | std::ios::app);

  if (outputFile.is_open()) {
    std::string compressedContent;
    try {
      compressedContent =
          bgit::services::CompressionService::compress(contentWithHeader);

      if (compressedContent.empty()) {
        std::cerr << "Error compressing object\n";
        outputFile.close();
        return false;
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
      return false;
    }

    outputFile << compressedContent;
  } else {
    std::cerr << "Error writing object to file\n";
    outputFile.close();
    return false;
  }

  outputFile.close();

  return true;
}

const bool HashObjectCommand::validateOptions(const int argc, char *argv[]) {
  if (argc == 3) {
    this->objectPath = argv[2];
  } else if (argc == 4) {
    std::string writeFlag = argv[2];
    if (writeFlag != "-w") {
      return UsageError();
    }

    this->writeObject = true;
    this->objectPath = argv[3];
  } else {
    return UsageError();
  }

  return true;
}

static const bool UsageError() {
  std::cerr << "Invalid number of arguments. Usage: bgit " << HASH_OBJECT
            << " [-w] <object-path>\n";
  return false;
}
} // namespace bgit::commands
