#pragma once

template<class Owner, typename ...FuncArgs>
class EventHandler
{
    using ReturnValue = void;
    using event = std::function<ReturnValue(FuncArgs...)>;
    using event_container = std::vector<event>;

    event_container events;

    friend Owner;

    ReturnValue operator()(FuncArgs... args)
    {
        for (auto& event : events)
            event(args...);
    }
public:
    void operator += (event method)
    {
        for (auto it = events.begin(); it != events.end(); it++)
            if (get_address(*it) == get_address(method))
                return;
        events.push_back(method);
    }
    void operator -= (event method)
    {
        for (auto it = events.begin(); it != events.end(); it++)
        {
            if (get_address(*it) == get_address(method))
            {
                events.erase(it);
                break;
            }
        }
    }

private:
    static size_t get_address(std::function<ReturnValue(FuncArgs...)> f) {
        typedef ReturnValue(fnType)(FuncArgs...);
        fnType** fnPointer = f.template target<fnType*>();
        return (size_t)*fnPointer;
    }
};