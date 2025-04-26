#include "EmailPreviewHeader.h"
#include "EmailRepo.h"
#include "EventBus.h"
#include "UserRepo.h"


EmailPreviewHeader::EmailPreviewHeader(Ref<DIContainer> const& diContainer, QWidget* parent)
    : QComponent("EmailPreviewHeader", parent)
    , m_DiContainer(diContainer)
    , m_SubjectValueLabel(new QLabel(this))
    , m_SenderLabel(new QLabel("Sender:", this))
    , m_SenderValueLabel(new QLabel(this))
    , m_RecipientsLabel(new QLabel("Recipient:", this))
    , m_RecipientsValueLabel(new QLabel(this))
{
    auto const layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    const int labelWidth = 100; 
    m_SenderLabel->setMinimumWidth(labelWidth);
    m_RecipientsLabel->setMinimumWidth(labelWidth);

    m_SenderLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_RecipientsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_SubjectValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_SenderValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_RecipientsValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_SubjectValueLabel->setProperty("class", "subject-value-label");
    layout->addWidget(m_SubjectValueLabel);

    // Sender row
    auto* senderLayout = new QHBoxLayout();
    senderLayout->addWidget(m_SenderLabel);
    senderLayout->addWidget(m_SenderValueLabel);
    layout->addLayout(senderLayout);

    // Recipients row
    auto* recipientsLayout = new QHBoxLayout();
    recipientsLayout->addWidget(m_RecipientsLabel);
    recipientsLayout->addWidget(m_RecipientsValueLabel);
    layout->addLayout(recipientsLayout);

    // Align text to the left
    m_SubjectValueLabel->setAlignment(Qt::AlignLeft);
    m_SenderLabel->setAlignment(Qt::AlignLeft);
    m_SenderValueLabel->setAlignment(Qt::AlignLeft);
    m_RecipientsLabel->setAlignment(Qt::AlignLeft);
    m_RecipientsValueLabel->setAlignment(Qt::AlignLeft);
}

EmailPreviewHeader::~EmailPreviewHeader() 
{
}

void EmailPreviewHeader::ProjectEmail(Email const& email)
{
    auto const& userRepo = m_DiContainer->GetService<UserRepo>();
    auto const& sender = userRepo->GetUser(email.SenderId);

    // Set subject
    m_SubjectValueLabel->setText(email.Subject);

    // Set sender
    m_SenderValueLabel->setText(sender.Email + " " + sender.FirstName + " " + sender.LastName);

    // Set recipients
    auto const& recipients = userRepo->GetRecipients(email.EmailId);
    QString recipientConcat;
    for (auto const& r : recipients)
        recipientConcat += r.Email + " " + r.FirstName + " " + r.LastName + "\n";

    m_RecipientsValueLabel->setText(recipientConcat.trimmed());
}

void EmailPreviewHeader::Clear() const
{
    m_SubjectValueLabel->setText("");
    m_SenderValueLabel->setText("");
    m_RecipientsValueLabel->setText("");
}
