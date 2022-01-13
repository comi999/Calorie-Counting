#pragma once
#include <iostream>

#include "CommandLine.hpp"
#include "Console.hpp"
#include "Text.hpp"

int main()
{
    string Something = "I am the best 'in the' world!";
    auto res = Text::Tokenize( Something );
    Command c( Something );
}