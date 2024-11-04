#pragma once

#include <string>
#include "../interfaces/ICommand.hpp"

namespace bgit::commands
{
    class HashObjectCommand : public bgit::interfaces::ICommand
    {
    private:
        bool writeObject;
        std::string objectPath;

    public:
        HashObjectCommand() {}
        ~HashObjectCommand() {}
        const bool execute() const override;
        const bool validateOptions(const int, char *[]) override;
    };
}