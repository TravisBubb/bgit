#pragma once

#include <memory>
#include "../interfaces/ICommand.hpp"
#include "../models/HashObjectOptions.hpp"

namespace bgit::commands
{
    class HashObjectCommand : public bgit::interfaces::ICommand
    {
    private:
        std::unique_ptr<bgit::models::HashObjectOptions> options;

    public:
        HashObjectCommand() {}
        ~HashObjectCommand() {}
        const int execute() const override;
        const int validateOptions(const int, char *[]) const override;
    };
}