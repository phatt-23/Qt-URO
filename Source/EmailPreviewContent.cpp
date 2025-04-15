#include "EmailPreviewContent.h"
#include "EmailCard.h"
#include "EmailRepo.h"
#include "EventBus.h"

EmailPreviewContent::EmailPreviewContent(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreviewContent", parent), m_DiContainer(diContainer)
    , m_Splitter(this)
    , m_Header(m_DiContainer, this)
    , m_Body(&m_Splitter)
    , m_Attachments(m_DiContainer, &m_Splitter)
{
    m_Splitter.setOrientation(Qt::Orientation::Vertical);
    m_Splitter.addWidget(&m_Body);          m_Splitter.setStretchFactor(0, 3);
    m_Splitter.addWidget(&m_Attachments);   m_Splitter.setStretchFactor(1, 1);


    // layout
    const auto layout = new QVBoxLayout(this);

    layout->addWidget(&m_Header); layout->setStretch(0, 0);
    layout->addWidget(&m_Splitter); layout->setStretch(1, 1);

    BindEvents();
}

void EmailPreviewContent::BindEvents()
{
    const auto bus = m_DiContainer->GetService<EventBus>();
    const auto emailRepo = m_DiContainer->GetService<EmailRepo>();

    bus->Subscribe<PreviewEmailClicked>([this, emailRepo](PreviewEmailClicked const& e) 
    {
        auto const& email = emailRepo->GetEmail(e.EmailId);
        ShowEmail(email);
    });
}

EmailPreviewContent::~EmailPreviewContent()
{
}

void EmailPreviewContent::ShowEmail(Email const& email)
{
    qInfo() << "Show email" << email;
    m_Header.ProjectEmail(email);
    m_Body.ProjectEmail(email);
    m_Attachments.ProjectEmail(email);
}

void EmailPreviewContent::HideEmail()
{
    qInfo() << "Hide email";

}

