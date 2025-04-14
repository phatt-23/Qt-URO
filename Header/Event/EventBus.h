//
// Created by phatt on 4/7/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H


#include "IService.h"


struct EventBase : public QObject {
    Q_OBJECT
public:
    EventBase() {}
    ~EventBase() override {}
};


inline QDebug operator<<(QDebug dbg, const EventBase& event)
{
    dbg.nospace() << "EventBase()";
    return dbg;
}



class EventBus final : public IService {
public:
    explicit EventBus() {}
    ~EventBus() override {}

    template <typename EventType>
    requires std::derived_from<EventType, EventBase>
    auto Subscribe(std::function<void(const EventType&)> handler) -> void
    {
        // get the name of the event type
        const std::string key = typeid(EventType).name();

        // wrap into closure that type checks the event data
        auto wrappedHandler = [handler](const EventBase& event) -> void
        {
            const auto& derivedEvent = dynamic_cast<const EventType&>(event);
            handler(derivedEvent);
        };

        // add to the map of callbacks
        m_Handlers[key].emplace_back(wrappedHandler);
    }

    template <typename EventType>
    requires std::derived_from<EventType, EventBase>
    auto Emit(const EventType& event) -> void
    {
        const char* key = typeid(EventType).name();

        qInfo() << "Emitting:" << event;

        const auto it = m_Handlers.find(key);
        if (it == m_Handlers.end())  // no handlers
            return;

        const auto eventHandlers = it->second;
        for (const auto& handler : eventHandlers)
            handler(event);
    }

    template <typename EventType, typename... Args>
    requires std::derived_from<EventType, EventBase>
    inline auto ForwardEmit(Args&& ...args) -> void
    {
        Emit(EventType(std::forward<Args>(args)...));
    }

private:
   std::map<std::string, std::vector<std::function<void(const EventBase& event)>>> m_Handlers;
};




#endif //EVENTBUS_H
