//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailPreview.h"
#include "EmailCard.h"

EmailPreview::EmailPreview(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreview", parent)
    , m_DiContainer(diContainer)
    , m_EmailPreviewToolbar(this)
    , m_EmailPreviewContent(m_DiContainer, this)
{
    const auto layout = new QVBoxLayout(this);

    layout->addWidget(&m_EmailPreviewToolbar); layout->setStretch(0, 0);
    layout->addWidget(&m_EmailPreviewContent); layout->setStretch(1, 1);

    BindEvents();
}

EmailPreview::~EmailPreview()
{
}

void EmailPreview::BindEvents()
{
    const auto bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<PreviewEmailClicked>([this](auto const& e) 
    {
        PreviewEmail(e.EmailId);
    });
}

void EmailPreview::PreviewEmail(int emailId)
{
    // TODO: Not implemented.
    qInfo() << "Show email with id" << emailId << "in the preview";
}
