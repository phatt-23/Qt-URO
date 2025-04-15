//
// Created by phatt on 4/7/25.
//

#ifndef SIDEBAR_H
#define SIDEBAR_H


#include "DIContainer.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"
#include "StdLib.h"
#include "ViewsEnum.h"


class SideBar final : public QComponent {
public:
    explicit SideBar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;

    QMap<ViewsEnum, QPushButton*> m_Buttons;
};


// Events
struct SideBarButtonClickedEvent final : public EventBase {
    explicit SideBarButtonClickedEvent(const ViewsEnum view) : View(view) {}
    ViewsEnum View;
};


inline QDebug operator<<(QDebug dbg, const SideBarButtonClickedEvent& event)
{
    dbg.nospace() << "SideBarButtonClickedEvent(View: " << event.View << ")";
    return dbg;
}


#endif //SIDEBAR_H
