#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <iostream>
#include <string>

#include "colorcodes.hpp"

namespace DebugOutput
{
    static inline void game(const std::string &text)
    {
        std::cout << GREEN << BRIGHT << "[Game]" << NORMAL << " " << text << std::endl;
    }

    static inline void gameState(const std::string &text)
    {
        std::cout << CYAN << BRIGHT << "    [GameState]" << NORMAL << " " << text << std::endl;
    }

    static inline void gameState(const std::string &state, const std::string &text)
    {
        std::cout << CYAN << BRIGHT << "    [GameState]" << NORMAL << " " << CYAN << "<" << state << ">" << NORMAL << " " << text << std::endl;
    }

    static inline void stateManager(const std::string &text)
    {
        std::cout << BLUE << BRIGHT << "  [StateManager]" << NORMAL << " " << text << std::endl;
    }
}


#endif // DEBUGOUTPUT_H
