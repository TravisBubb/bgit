#pragma once

namespace bgit::interfaces
{
    class ICommand
    {
    public:
        virtual ~ICommand() {}
        const virtual bool execute() const = 0;
        const virtual bool validateOptions(const int, char *[]) = 0;
    };
}