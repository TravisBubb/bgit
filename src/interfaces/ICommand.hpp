#pragma once

namespace bgit::interfaces
{
    class ICommand
    {
    public:
        virtual ~ICommand() {}
        const virtual int execute() const = 0;
        const virtual int validateOptions(const int, char *[]) const = 0;
    };
}