//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailList.h"

#include "EmailView/EmailListViews/InboxListView.h"

EmailList::EmailList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailList", parent), m_DiContainer(diContainer)
    , m_SearchBar(m_DiContainer, this)
    , m_FilterFrame(m_DiContainer, this)
    , m_SortFrame(m_DiContainer, this)
    , m_CurrentListView()
{
    // insert views
    m_ListViews.insert(EmailListViews::INBOX_LIST_VIEW, new InboxListView(m_DiContainer, this));

    // ...


    // layout
    const auto layout = new QVBoxLayout(this);

    layout->addWidget(&m_SearchBar);
    layout->addWidget(&m_FilterFrame);
    layout->addWidget(&m_SortFrame);

    m_SearchBar.show();
    m_FilterFrame.hide();
    m_SortFrame.hide();

    for (const auto& view : m_ListViews.values())
        layout->addWidget(view);
    HideAllViews();

    m_SearchBar.setFixedHeight(40);

    for (std::size_t i = 1; i < m_ListViews.count(); i++)
        layout->setStretch(i, 6);


    // show current
    m_CurrentListView = EmailListViews::INBOX_LIST_VIEW;

    HideAllViews();
    m_ListViews[m_CurrentListView]->show();
}

void EmailList::HideAllViews() const
{
    for (const auto& view : m_ListViews.values())
        view->hide();
}

