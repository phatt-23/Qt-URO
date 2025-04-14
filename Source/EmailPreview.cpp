//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailPreview.h"

EmailPreview::EmailPreview(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreview", parent)
    , m_DiContainer(diContainer)
    , m_EmailPreviewToolbar(this)
    , m_EmailPreviewContent(m_DiContainer, this)
{
    const auto layout = new QVBoxLayout(this);

    layout->addWidget(&m_EmailPreviewToolbar); layout->setStretch(0, 0);
    layout->addWidget(&m_EmailPreviewContent); layout->setStretch(1, 1);

}


EmailPreview::~EmailPreview()
{
}
