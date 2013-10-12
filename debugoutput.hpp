#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <iostream>
#include <string>

namespace DebugOutput
{
    static inline void game(const std::string &text)
    {
        std::cout << "[Game] " << text << std::endl;
    }

    static inline void gameState(const std::string &text)
    {
        std::cout << "    [GameState] " << text << std::endl;
    }

    static inline void gameState(const std::string &state, const std::string &text)
    {
        std::cout << "    [GameState] <" << state << "> " << text << std::endl;
    }

    static inline void stateManager(const std::string &text)
    {
        std::cout << "  [StateManager] " << text << std::endl;
    }
}


#endif // DEBUGOUTPUT_H
