
#include "EmailCard.h"


EmailCard::EmailCard(const Email& email, const QString& sender, QWidget* parent)
    : QComponent("EmailCard", parent)
    , m_EmailId(email.EmailId)
    , m_SenderLabel(this)
    , m_SentAtLabel(this)
    , m_SubjectLabel(this)
    , m_PreviewButton("Preview", this)
{
    // layout
    const auto layout = new QGridLayout(this);

    m_SenderLabel.setText(sender);
    m_SubjectLabel.setText(email.Subject);
    m_SentAtLabel.setText(email.SentAt);

    layout->addWidget(&m_SenderLabel, 0, 0, Qt::AlignLeft);
    layout->addWidget(&m_SentAtLabel, 0, 1, Qt::AlignRight);

    layout->addWidget(&m_SubjectLabel, 1, 0, Qt::AlignLeft);
    layout->addWidget(&m_PreviewButton, 1, 1, Qt::AlignRight);
}

EmailCard::~EmailCard() 
{
}
