//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/CategoryList.h"

#include "EventBus.h"

CategoryList::CategoryList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("CategoryList", parent)
    , m_DiContainer(diContainer)
    , m_LastClickedButton(nullptr)
{
    m_Buttons[INBOX] = new QPushButton("Inbox", this);
    m_Buttons[DRAFTS] = new QPushButton("Drafts", this);
    m_Buttons[SENT_MAIL] = new QPushButton("Sent Mail", this);
    m_Buttons[ALL_MAIL] = new QPushButton("All Mail", this);
    m_Buttons[BIN] = new QPushButton("Bin", this);
    m_Buttons[SPAM] = new QPushButton("Spam", this);
    m_Buttons[IMPORTANT] = new QPushButton("Important", this);
    m_Buttons[STARRED] = new QPushButton("Starred", this);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->setAlignment(Qt::AlignTop);

    for (const auto& button : m_Buttons)
    {
        layout->addWidget(button);
    }

    BindEvents();
}

void CategoryList::BindEvents()
{
    auto bus = m_DiContainer->GetService<EventBus>();

    for (auto const& button : m_Buttons.values())
    {
        button->setCheckable(true);
    }

    connect(m_Buttons[INBOX], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(INBOX);
        bus->ForwardEmit<InboxItemClickedEvent>();
    });

    connect(m_Buttons[DRAFTS], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(DRAFTS);
        bus->ForwardEmit<DraftsItemClickedEvent>();
    });

    connect(m_Buttons[SENT_MAIL], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(SENT_MAIL);
        bus->ForwardEmit<SentMailItemClickedEvent>();
    });

    connect(m_Buttons[ALL_MAIL], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(ALL_MAIL);
        bus->ForwardEmit<AllMailItemClickedEvent>();
    });

    connect(m_Buttons[BIN], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(BIN);
        bus->ForwardEmit<BinItemClickedEvent>();
    });

    connect(m_Buttons[SPAM], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(SPAM);
        bus->ForwardEmit<SpamItemClickedEvent>();
    });

    connect(m_Buttons[IMPORTANT], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(IMPORTANT);
        bus->ForwardEmit<ImportantItemClickedEvent>();
    });

    connect(m_Buttons[STARRED], &QPushButton::clicked, this, [this, bus]() {
        SetLastClickedButton(STARRED);
        bus->ForwardEmit<StarredItemClickedEvent>();
    });
}

void CategoryList::SetLastClickedButton(CategoryListButton const button)
{
    if (m_LastClickedButton)
    {
        m_LastClickedButton->setChecked(false);
    }

    m_LastClickedButton = m_Buttons[button];
    m_LastClickedButton->setChecked(true);
}
