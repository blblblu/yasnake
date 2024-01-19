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
    struct SubmitScoreEvent{
        SubmitScoreEvent(){}
        SubmitScoreEvent(int score) : score(score){}
        int score;
    };

    enum class EventType{
        ReplaceState,
        PushState,
        PopState,

        SubmitScoreEvent,

        Count
    };

    EventType type;

    boost::variant<StateChangeEvent, SubmitScoreEvent> data;
};

#endif // STATEEVENT_H
