#include "EmailPreviewToolbar.h"


EmailPreviewToolbar::EmailPreviewToolbar(QWidget* parent)
    : QComponent("EmailPreviewToolbar", parent)
{
    m_Buttons[REPLY] = new QPushButton("Reply", this);
    m_Buttons[FORWARD] = new QPushButton("Forward", this);
    m_Buttons[REMOVE] = new QPushButton("Remove", this);
    m_Buttons[DELETE_FOREVER] = new QPushButton("Delete Forever", this);
    m_Buttons[EDIT] = new QPushButton("Edit", this);
    m_Buttons[CLOSE] = new QPushButton("Close", this);

    const auto layout = new QHBoxLayout(this);
    
    for (const auto& button : m_Buttons.values())
    {
        layout->addWidget(button);
    }

    m_Buttons[DELETE_FOREVER]->hide();
}


EmailPreviewToolbar::~EmailPreviewToolbar()
{
}

