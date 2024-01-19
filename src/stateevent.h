#pragma once

#include <string>
#include <variant>

class StateEvent
{
public:
    struct StateChangeEvent
    {
        StateChangeEvent() {}
        StateChangeEvent(std::string name) : name(name) {}
        std::string name;
    };
    struct SubmitScoreEvent
    {
        SubmitScoreEvent() {}
        SubmitScoreEvent(int score) : score(score) {}
        int score;
    };

    enum class EventType
    {
        ReplaceState,
        PushState,
        PopState,

        SubmitScoreEvent,

        Count
    };

    EventType type;

    std::variant<StateChangeEvent, SubmitScoreEvent> data;
};
