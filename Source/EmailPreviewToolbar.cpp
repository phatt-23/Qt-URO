#include "EmailPreviewToolbar.h"

EmailPreviewToolbar::EmailPreviewToolbar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreviewToolbar", parent)
    , m_DiContainer(diContainer)
{
    m_Buttons[REPLY] = new QPushButton("Reply", this);
    m_Buttons[FORWARD] = new QPushButton("Forward", this);
    m_Buttons[REMOVE] = new QPushButton("Remove", this);
    m_Buttons[DELETE_FOREVER] = new QPushButton("Delete Forever", this);
    m_Buttons[EDIT] = new QPushButton("Edit", this);
    m_Buttons[CLOSE] = new QPushButton("Close", this);

    const auto layout = new QHBoxLayout(this);

    layout->addWidget(m_Buttons[REPLY]);
    layout->addWidget(m_Buttons[FORWARD]);
    layout->addWidget(m_Buttons[REMOVE]);
    layout->addWidget(m_Buttons[DELETE_FOREVER]);
    layout->addWidget(m_Buttons[EDIT]);
    layout->addStretch();
    layout->addWidget(m_Buttons[CLOSE]);

    HideButtons();
}


EmailPreviewToolbar::~EmailPreviewToolbar()
{
}

void EmailPreviewToolbar::HideButtons() const
{
    for (const auto& button : m_Buttons.values())
    {
        button->hide();
    }

    m_Buttons[CLOSE]->show();
}

