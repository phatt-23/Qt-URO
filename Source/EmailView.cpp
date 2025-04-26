//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/EmailView.h"

#include "EmailCard.h"

EmailView::EmailView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : BaseView("EmailView", parent)
    , m_DiContainer(diContainer)
    , m_Splitter(Qt::Horizontal, this)
    , m_CategoryList(diContainer, this)
    , m_EmailList(diContainer, this)
    , m_EmailPreview(diContainer, this)
    , m_Layout(new QVBoxLayout(this))

{
    // split frames
    m_Splitter.addWidget(&m_CategoryList);
    m_Splitter.addWidget(&m_EmailList);
    m_Splitter.addWidget(&m_EmailPreview);
    // m_Splitter.setContentsMargins(0, 0, 0, 0);

    m_Splitter.setStretchFactor(0, 0);
    m_Splitter.setStretchFactor(1, 5);
    m_Splitter.setStretchFactor(2, 5);

    // layout
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);
    m_Layout->addWidget(&m_Splitter);

    BindEvents();
}

EmailView::~EmailView()
{
}

void EmailView::BindEvents()
{
    m_DiContainer->GetService<EventBus>()->Subscribe<CloseButtonClickedEvent>([this](CloseButtonClickedEvent const& e)
    {
        m_EmailPreview.hide();
    });

    m_DiContainer->GetService<EventBus>()->Subscribe<PreviewEmailClicked>([this](PreviewEmailClicked const& e)
    {
        m_EmailPreview.show();
    });

}
