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
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // layout children
    layout->addWidget(m_Buttons[ViewsEnum::COMPOSE_VIEW]);
    layout->addWidget(m_Buttons[ViewsEnum::EMAIL_VIEW]);
    layout->addWidget(m_Buttons[ViewsEnum::CONTACTS_VIEW]);

    layout->addStretch();

    layout->addWidget(m_Buttons[ViewsEnum::LOGOUT]);
    layout->addWidget(m_Buttons[ViewsEnum::QUIT]);

    for (auto& button : m_Buttons)
    {
        button->setProperty("class", "sidebar_button");
    }

    BindEvents();
}

void SideBar::BindEvents()
{
    // events
    const auto bus = m_DiContainer->GetService<EventBus>();

    connect(m_Buttons[ViewsEnum::COMPOSE_VIEW], &QPushButton::clicked, [this, bus]{
        SetLastClickedButton(ViewsEnum::COMPOSE_VIEW);
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::COMPOSE_VIEW);
    });

    connect(m_Buttons[ViewsEnum::EMAIL_VIEW], &QPushButton::clicked, [this, bus]{
        SetLastClickedButton(ViewsEnum::EMAIL_VIEW);
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::EMAIL_VIEW);
    });

    connect(m_Buttons[ViewsEnum::CONTACTS_VIEW], &QPushButton::clicked, [this, bus]{
        SetLastClickedButton(ViewsEnum::CONTACTS_VIEW);
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::CONTACTS_VIEW);
    });

    connect(m_Buttons[ViewsEnum::QUIT], &QPushButton::clicked, [this, bus]{
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::QUIT);
    });

    connect(m_Buttons[ViewsEnum::LOGOUT], &QPushButton::clicked, [this, bus]{
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::LOGOUT);
    });
}

void SideBar::SetLastClickedButton(ViewsEnum const view)
{
    if (m_LastClickedButton)
    {
        m_LastClickedButton->setChecked(false);
    }

    m_LastClickedButton = m_Buttons[view];
    m_LastClickedButton->setChecked(true);

}