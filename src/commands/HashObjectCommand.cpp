#include "HashObjectCommand.hpp"
#include "../Constants.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>
#include <zlib.h>
#include <openssl/evp.h>

namespace bgit::commands
{
    static const bool UsageError();

    const bool HashObjectCommand::execute() const
    {
        std::ifstream file(this->objectPath, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << this->objectPath << '\n';
            return false;
        }

        EVP_MD_CTX *ctx = EVP_MD_CTX_new();
        if (!ctx)
        {
            std::cerr << "Error creating EVP_MD_CTX\n";
            return false;
        }

        if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1)
        {
            std::cerr << "Error initializing digest\n";
            EVP_MD_CTX_free(ctx);
            return false;
        }

        const int BUFFER_SIZE = 4096;
        unsigned char buffer[BUFFER_SIZE];
        while (file)
        {
            file.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE);
            std::streamsize bytesRead = file.gcount();
            if (bytesRead > 0)
            {
                if (EVP_DigestUpdate(ctx, buffer, bytesRead) != 1)
                {
                    std::cerr << "Error updating digest\n";
                    EVP_MD_CTX_free(ctx);
                    return false;
                }
            }
        }

        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hashLength;
        if (EVP_DigestFinal_ex(ctx, hash, &hashLength) != 1)
        {
            std::cerr << "Error finalizing digest\n";
            EVP_MD_CTX_free(ctx);
            return false;
        }

        EVP_MD_CTX_free(ctx);

        for (unsigned int i = 0; i < hashLength; ++i)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        std::cout << '\n';

        if (!this->writeObject)
            return true;

        // if writeObject is true, then attempt to write it to .git/objects/{first 2 chars of hash}/{last 38 chars of hash}
        //      remember the data should have a standard format blob {length}\0{content} and then also be compressed with zlib

        return true;
    }

    const bool HashObjectCommand::validateOptions(const int argc, char *argv[])
    {
        if (argc == 3)
        {
            this->objectPath = argv[2];
        }
        else if (argc == 4)
        {
            std::string writeFlag = argv[2];
            if (writeFlag != "-w")
            {
                return UsageError();
            }

            this->writeObject = true;
            this->objectPath = argv[3];
        }
        else
        {
            return UsageError();
        }

        return true;
    }

    static const bool UsageError()
    {
        std::cerr << "Invalid number of arguments. Usage: bgit " << HASH_OBJECT << " [-w] <object-path>\n";
        return false;
    }
}