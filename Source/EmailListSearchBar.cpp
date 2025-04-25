//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailListSearchBar.h"

EmailListSearchBar::EmailListSearchBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailListSearchBar", parent), m_DiContainer(diContainer)
    , m_Input(this)
    , m_SearchButton("Search", this)
    , m_FilterOptionsButton("Filter", this)
    , m_SortOptionsButton("Sort", this)
    , m_FilterFrame(diContainer, this)
    , m_SortFrame(diContainer, this)
{
    m_Input.setPlaceholderText("Search...");


    const auto horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(&m_Input);
    horizontalLayout->addWidget(&m_SearchButton);
    horizontalLayout->addWidget(&m_FilterOptionsButton);
    horizontalLayout->addWidget(&m_SortOptionsButton);

    m_SortOptionsButton.hide();

    const auto layout = new QVBoxLayout(this);
    layout->addLayout(horizontalLayout);
    layout->addWidget(&m_FilterFrame);
    layout->addWidget(&m_SortFrame);

    m_FilterFrame.setVisible(false);
    m_SortFrame.setVisible(false);

    BindEvents();
}

void EmailListSearchBar::BindEvents()
{
    connect(&m_SearchButton, &QPushButton::clicked, this, &EmailListSearchBar::OnSearchButtonClicked);
    connect(&m_FilterOptionsButton, &QPushButton::clicked, this, &EmailListSearchBar::OnFilterButtonClicked);
    // connect(&m_SortOptionsButton, &QPushButton::clicked, this, &EmailListSearchBar::OnSortButtonClicked);
}

void EmailListSearchBar::OnSearchButtonClicked()
{
    emit EmailSearchEvent(m_Input.text());
}

void EmailListSearchBar::OnFilterButtonClicked()
{
    m_FilterFrame.setVisible(!m_FilterFrame.isVisible());
}

void EmailListSearchBar::OnSortButtonClicked()
{
    m_SortFrame.setVisible(!m_SortFrame.isVisible());
}



