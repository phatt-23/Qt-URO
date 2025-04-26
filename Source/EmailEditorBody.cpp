//
// Created by phatt on 4/26/25.
//

#include "../Header/Views/ComposeView/EmailEditorBody.h"

EmailEditorBody::EmailEditorBody(QWidget* parent): QComponent("EmailEditorBody", parent)
                                                   , m_TextBody(new QTextEdit(this))
{
    // body frame
    m_TextBody->setPlaceholderText("Start typing...");


    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_TextBody);
}
