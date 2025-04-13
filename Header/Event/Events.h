//
// Created by phatt on 4/7/25.
//

#ifndef EVENTS_H
#define EVENTS_H


#include "EventBus.h"


struct ButtonClickedEvent : public EventBase {
    explicit ButtonClickedEvent(const std::string& m) : ButtonId{m} {}
    std::string ButtonId;
};





#endif //EVENTS_H
