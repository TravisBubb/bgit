#pragma once

namespace bgit::interfaces
{
    class ICommand
    {
    public:
        virtual ~ICommand() {}
        virtual int execute() const = 0;
    };
}