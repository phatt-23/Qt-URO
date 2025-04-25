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
    m_Splitter.addWidget(&m_Body);
    m_Splitter.addWidget(&m_Attachments);

    // Set initial sizes for the splitter
    QList<int> sizes = {300, 150}; 
    m_Splitter.setSizes(sizes);

    m_Attachments.hide();

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
    m_Attachments.ProjectEmail(email.EmailId);
    m_Email = email;
}

void EmailPreviewContent::HideEmail()
{
    qInfo() << "Hide email";
    m_Header.Clear();
    m_Body.Clear();
    m_Attachments.Clear();
    m_Email = std::nullopt;
}

