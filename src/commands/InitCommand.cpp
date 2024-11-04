#include <iostream>
#include <filesystem>
#include <fstream>
#include "InitCommand.hpp"

namespace bgit::commands
{
    const bool InitCommand::execute() const
    {
        try
        {
            std::filesystem::create_directory(".bgit");
            std::filesystem::create_directory(".bgit/objects");
            std::filesystem::create_directory(".bgit/refs");

            std::ofstream headFile(".bgit/HEAD");
            if (headFile.is_open())
            {
                headFile << "ref: refs/heads/main\n";
                headFile.close();
            }
            else
            {
                std::cerr << "Failed to create .bgit/HEAD file.\n";
                return false;
            }

            std::cout << "Initialized git directory\n";
            return true;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }
}