//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailList.h"

#include "AllMailListView.h"
#include "BinListView.h"
#include "DraftsListView.h"
#include "EmailRepo.h"
#include "SentMailListView.h"
#include "EmailView/CategoryList.h"
#include "EmailView/EmailListViews/InboxListView.h"

EmailList::EmailList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailList", parent), m_DiContainer(diContainer)
    , m_SearchBar(m_DiContainer, this)
    , m_CurrentListView()
{
    // insert views
    m_ListViews.insert(INBOX_LIST_VIEW, new InboxListView(m_DiContainer, this));
    m_ListViews.insert(DRAFT_LIST_VIEW, new DraftsListView(m_DiContainer, this));
    m_ListViews.insert(SENT_MAIL_LIST_VIEW, new SentMailListView(m_DiContainer, this));
    m_ListViews.insert(ALL_MAIL_LIST_VIEW, new AllMailListView(m_DiContainer, this));
    m_ListViews.insert(BIN_LIST_VIEW, new BinListView(m_DiContainer, this));
    // ...


    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setStretch(0, 0);

    layout->addWidget(&m_SearchBar);  // index 0

    for (const auto& view : m_ListViews.values())
    {
        layout->addWidget(view);
    }

    for (std::size_t i = 1; i < m_ListViews.count(); i++)
    {
        layout->setStretch(i, 6);
    }

    // hide all and show current
    HideAllViews();

    m_CurrentListView = EmailListViews::INBOX_LIST_VIEW;
    m_ListViews[m_CurrentListView]->show();

    BindEvents();
}

void EmailList::HideAllViews() const
{
    for (const auto& view : m_ListViews.values())
    {
        view->hide();
    }
}

void EmailList::BindEvents()
{
    const auto bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<InboxItemClickedEvent>([this](const InboxItemClickedEvent& e)
    {
        SetCurrentView(INBOX_LIST_VIEW);
    });

    bus->Subscribe<DraftsItemClickedEvent>([this](const DraftsItemClickedEvent& e)
    {
        SetCurrentView(DRAFT_LIST_VIEW);
    });

    bus->Subscribe<SentMailItemClickedEvent>([this](const SentMailItemClickedEvent& e)
    {
        SetCurrentView(SENT_MAIL_LIST_VIEW);
    });

    bus->Subscribe<AllMailItemClickedEvent>([this](const AllMailItemClickedEvent& e)
    {
        SetCurrentView(ALL_MAIL_LIST_VIEW);
    });

    bus->Subscribe<BinItemClickedEvent>([this](const BinItemClickedEvent& e)
    {
        SetCurrentView(BIN_LIST_VIEW);
    });

    bus->Subscribe<EmailStatusChangedEvent>([this](const EmailStatusChangedEvent& e)
    {
        // show any changes that happened
        m_ListViews[m_CurrentListView]->ShowEmails();
    });

    connect(&m_SearchBar, &EmailListSearchBar::EmailSearchEvent, [this](QString const& searchString)
    {
        qInfo() << "Search string:" << searchString;
        qInfo() << "Put in like this:" << '%' + searchString.trimmed().toLower() + '%'
        m_ListViews[m_CurrentListView]->ShowEmails(searchString);
    });
}

void EmailList::SetCurrentView(EmailListViews const view)
{
    HideAllViews();
    m_CurrentListView = view;
    m_ListViews[m_CurrentListView]->show();
    m_ListViews[m_CurrentListView]->ShowEmails();
}

