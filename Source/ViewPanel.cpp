//
// Created by phatt on 4/7/25.
//

#include "../Header/ViewPanel.h"

#include "ContactsView.h"
#include "ComposeView.h"
#include "EmailView.h"
#include "SideBar.h"

ViewPanel::ViewPanel(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("ViewPanel", parent), m_DiContainer(diContainer)
{
    // children
    m_Views.insert(ViewsEnum::EMAIL_VIEW, new EmailView(diContainer, this));
    m_Views.insert(ViewsEnum::COMPOSE_VIEW, new ComposeView(diContainer, this));
    m_Views.insert(ViewsEnum::CONTACTS_VIEW, new ContactsView(diContainer, this));

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    for (auto it = m_Views.begin(); it != m_Views.end(); ++it)
    {
        layout->addWidget(it.value());
        it.value()->hide();
    }

    // initial view
    ShowView(ViewsEnum::EMAIL_VIEW);

    BindEvents();
}

void ViewPanel::BindEvents()
{
    // events
    const auto bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<SideBarButtonClickedEvent>([this](const auto& e) {
        qInfo() << "ViewPanel - Received:" << e;
        ShowView(e.View);
    });

    bus->Subscribe<EditButtonClickedEvent>([this](EditButtonClickedEvent const& e)
    {
        ShowView(ViewsEnum::COMPOSE_VIEW);
    });
}

void ViewPanel::ShowView(ViewsEnum const view)
{
    if (m_Views.contains(view))
    {
        // hide all
        for (const auto& widget : m_Views.values())
            widget->hide();

        // show selected
        m_Views[view]->show();
        m_Views[view]->OnEnter();
    }
}
