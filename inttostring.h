#ifndef INTTOSTRING_H
#define INTTOSTRING_H

#include <sstream>
#include <string>

static inline std::string intToString(int i)
{
    std::stringstream strstream;
    strstream << i;
    return strstream.str();
}

#endif // INTTOSTRING_H
