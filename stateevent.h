#ifndef STATEEVENT_H
#define STATEEVENT_H

#include <string>

class StateEvent
{
public:
    struct StateChangeEvent{
        string name;
    };

    enum EventType{
        ReplaceState,
        PushState,
        PopState
    };

    EventType type;

    union{
        StateChangeEvent state;
    };
};

#endif // STATEEVENT_H
