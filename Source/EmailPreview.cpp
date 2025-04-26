//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailPreview.h"
#include "EmailCard.h"
#include "EmailRepo.h"

EmailPreview::EmailPreview(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreview", parent)
    , m_DiContainer(diContainer)
    , m_EmailPreviewToolbar(diContainer, this)
    , m_EmailPreviewContent(m_DiContainer, this)
{
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(&m_EmailPreviewToolbar); layout->setStretch(0, 0);
    layout->addWidget(&m_EmailPreviewContent); layout->setStretch(1, 1);

    BindEvents();
}

EmailPreview::~EmailPreview()
{
}

void EmailPreview::Show()
{
    m_EmailPreviewToolbar.show();
    m_EmailPreviewContent.show();
}

void EmailPreview::Hide()
{
    m_EmailPreviewToolbar.hide();
    m_EmailPreviewContent.hide();
}

void EmailPreview::BindEvents()
{
    const auto bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<PreviewEmailClicked>([this](auto const& e) 
    {
        PreviewEmail(e.EmailId);
    });

    // REPLY,
    // FORWARD,
    // REMOVE,
    // DELETE_FOREVER,
    // EDIT,
    // CLOSE,

    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::REPLY], &QPushButton::clicked, [this]()
    {
        // nothing
    });


    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::FORWARD], &QPushButton::clicked, [this]()
    {
        // nothing
    });

    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::REMOVE], &QPushButton::clicked, [this]()
    {
        // nothing
        const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
        emailRepo->SetEmailStatus(m_EmailPreviewContent.m_Email->EmailId, EmailStatus::REMOVED);
        m_EmailPreviewContent.HideEmail();
    });

    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::DELETE_FOREVER], &QPushButton::clicked, [this]()
    {
        const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
        emailRepo->SetEmailStatus(m_EmailPreviewContent.m_Email->EmailId, EmailStatus::DELETED);
        m_EmailPreviewContent.HideEmail();
    });

    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::EDIT], &QPushButton::clicked, [this]()
    {
        // nothing
        m_DiContainer->GetService<EventBus>()->ForwardEmit<EditButtonClickedEvent>(m_EmailPreviewContent.m_Email->EmailId);
    });

    connect(m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::CLOSE], &QPushButton::clicked, [this]()
    {
        m_DiContainer->GetService<EventBus>()->ForwardEmit<CloseButtonClickedEvent>();
    });
}

void EmailPreview::PreviewEmail(const int emailId)
{
    qInfo() << "Show email with id" << emailId << "in the preview";
    auto const email = m_DiContainer->GetService<EmailRepo>()->GetEmail(emailId);
    m_EmailPreviewContent.ShowEmail(email);

    m_EmailPreviewToolbar.HideButtons();

    switch (email.Status)
    {
    case EmailStatus::DRAFT:
        {
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::EDIT]->show();
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::REMOVE]->show();
        } break;
    case EmailStatus::REMOVED:
        {
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::DELETE_FOREVER]->show();
        } break;
    default:
        {
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::REPLY]->show();
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::FORWARD]->show();
            m_EmailPreviewToolbar.m_Buttons[EmailPreviewToolbar::REMOVE]->show();
        }
    }


}
