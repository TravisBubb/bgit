#include <iostream>
#include "CommandFactory.hpp"
#include "interfaces/ICommand.hpp"

int main(int argc, char *argv[])
{
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2)
    {
        std::cerr << "Invalid number of arguments. Usage: bgit <command> | <options>\n";
        return EXIT_FAILURE;
    }

    std::string commandType = argv[1];

    bgit::CommandFactory factory;

    const std::unique_ptr<bgit::interfaces::ICommand> command = factory.Create(commandType);

    if (command == nullptr)
    {
        std::cerr << "Unknown command \"" << commandType << "\"\n";
        return EXIT_FAILURE;
    }

    if (!command->execute())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}