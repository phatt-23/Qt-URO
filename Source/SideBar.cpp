//
// Created by phatt on 4/7/25.
//

#include "../Header/SideBar.h"

#include "EventBus.h"
#include "Events.h"


SideBar::SideBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("Sidebar", parent), m_DiContainer(diContainer)
{
    // initialize children
    m_Buttons.insert(ViewsEnum::COMPOSE_VIEW, new QPushButton("Compose", this));
    m_Buttons.insert(ViewsEnum::EMAIL_VIEW, new QPushButton("Inbox", this));
    m_Buttons.insert(ViewsEnum::CONTACTS_VIEW, new QPushButton("Contact", this));
    m_Buttons.insert(ViewsEnum::QUIT, new QPushButton("Quit", this));
    m_Buttons.insert(ViewsEnum::LOGOUT, new QPushButton("Log-Out", this));


    // setup layout
    const auto layout = new QVBoxLayout(this);

    // layout children
    layout->addWidget(m_Buttons[ViewsEnum::COMPOSE_VIEW]);
    layout->addWidget(m_Buttons[ViewsEnum::EMAIL_VIEW]);
    layout->addWidget(m_Buttons[ViewsEnum::CONTACTS_VIEW]);

    layout->addStretch();

    layout->addWidget(m_Buttons[ViewsEnum::LOGOUT]);
    layout->addWidget(m_Buttons[ViewsEnum::QUIT]);


    // events
    const auto bus = m_DiContainer->GetService<EventBus>();

    connect(m_Buttons[ViewsEnum::COMPOSE_VIEW], &QPushButton::clicked, this, [bus]{
        bus->Emit(SideBarButtonClickedEvent{ ViewsEnum::COMPOSE_VIEW });
    });

    connect(m_Buttons[ViewsEnum::EMAIL_VIEW], &QPushButton::clicked, this, [bus]{
        bus->Emit(SideBarButtonClickedEvent{ ViewsEnum::EMAIL_VIEW });
    });

    connect(m_Buttons[ViewsEnum::CONTACTS_VIEW], &QPushButton::clicked, this, [bus]{
        bus->Emit(SideBarButtonClickedEvent{ ViewsEnum::CONTACTS_VIEW });
    });

    connect(m_Buttons[ViewsEnum::QUIT], &QPushButton::clicked, this, [bus]{
        bus->Emit(SideBarButtonClickedEvent{ ViewsEnum::QUIT });
    });

    connect(m_Buttons[ViewsEnum::LOGOUT], &QPushButton::clicked, this, [bus]{
        bus->Emit(SideBarButtonClickedEvent{ ViewsEnum::LOGOUT });
    });

}
