//
// Created by phatt on 4/7/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H


#include "IService.h"
#include <typeindex>


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
        const std::type_index key = typeid(EventType);

        auto wrappedHandler = [handler](const EventBase& event) {
            const auto& derivedEvent = dynamic_cast<const EventType&>(event);
            handler(derivedEvent);
        };

        m_Handlers[key].push_back(wrappedHandler);
    }

    template <typename EventType>
    requires std::derived_from<EventType, EventBase>
    auto Emit(const EventType& event) -> void
    {
        const std::type_index key = typeid(EventType);

        qInfo() << "Emitting:" << event << " with key:" << QString::fromStdString(key.name());

        auto it = m_Handlers.find(key);
        if (it == m_Handlers.end()) {
            qInfo() << "No handlers for event type";
            return;
        }

        const auto& eventHandlers = it->second;
        qInfo() << "There are" << eventHandlers.size() << "listeners.";

        for (const auto& handler : eventHandlers)
            handler(event);
    }



    template <typename EventType, typename... Args>
    requires std::derived_from<EventType, EventBase>
    inline auto ForwardEmit(Args&& ...args) -> void
    {
        EventType event(std::forward<Args>(args)...);
        Emit(event);
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const EventBase& event)>>> m_Handlers;
};




#endif //EVENTBUS_H
