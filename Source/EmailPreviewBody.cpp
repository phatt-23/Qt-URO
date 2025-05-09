#include "EmailPreviewBody.h"


EmailPreviewBody::EmailPreviewBody(QWidget* parent)
    : QComponent("EmailPreviewBody", parent)
    , m_TextEdit(this)
{
    m_TextEdit.setPlaceholderText("Email body...");
    m_TextEdit.setReadOnly(true);

    auto const& layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(&m_TextEdit);
}

EmailPreviewBody::~EmailPreviewBody()
{
}

void EmailPreviewBody::ProjectEmail(Email const& email)
{
    m_TextEdit.setText(email.Body);
}
