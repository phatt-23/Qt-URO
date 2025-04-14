#include "EmailPreviewHeader.h"
#include "EmailRepo.h"
#include "EventBus.h"
#include "UserRepo.h"


EmailPreviewHeader::EmailPreviewHeader(Ref<DIContainer> const& diContainer, QWidget* parent)
    : QComponent("EmailPreviewHeader", parent)
    , m_DiContainer(diContainer)
    , m_SubjectLabel("[subject]", this)
    , m_SenderLabel("[sender]", this)
    , m_RecipientsLabel("[recipients]", this)
{
    auto const& layout = new QVBoxLayout(this);

    layout->addWidget(&m_SubjectLabel);
    layout->addWidget(&m_SenderLabel);
    layout->addWidget(&m_RecipientsLabel);
}

EmailPreviewHeader::~EmailPreviewHeader() 
{
}

void EmailPreviewHeader::ProjectEmail(Email const& email)
{
    auto const& userRepo = m_DiContainer->GetService<UserRepo>();
    auto const& emailRepo = m_DiContainer->GetService<EmailRepo>();
    auto const& sender = userRepo->GetUser(email.SenderId);

    m_SubjectLabel.setText(email.Subject);
   
    m_SenderLabel.setText(sender.Email + " " + sender.FirstName + " " + sender.LastName);

    auto const& recipients = userRepo->GetRecipients(email.EmailId);
   
    QString recipientConcat;
    for (auto const& r : recipients)
        recipientConcat += r.Email + " " + r.FirstName + " " + r.LastName + "\n";

    m_RecipientsLabel.setText(recipientConcat);
}
