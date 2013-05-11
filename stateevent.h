#ifndef STATEEVENT_H
#define STATEEVENT_H

#include <string>

#include <boost/variant.hpp>

class StateEvent
{
public:
    struct StateChangeEvent{
        StateChangeEvent(){}
        StateChangeEvent(std::string name) : name(name){}
        std::string name;
    };

    enum EventType{
        ReplaceState,
        PushState,
        PopState,

        Count
    };

    EventType type;

    boost::variant<StateChangeEvent> data;
};

#endif // STATEEVENT_H
