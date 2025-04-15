//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/EmailView.h"

EmailView::EmailView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailView", parent), m_DiContainer(diContainer)
    , m_Splitter(Qt::Horizontal, this)
    , m_CategoryList(diContainer, this)
    , m_EmailList(diContainer, this)
    , m_EmailPreview(diContainer, this)
{
    // split frames
    m_Splitter.addWidget(&m_CategoryList);
    m_Splitter.addWidget(&m_EmailList);
    m_Splitter.addWidget(&m_EmailPreview);

    m_Splitter.setSizes({150, 500, 500}); // set init sizes
    m_CategoryList.setMinimumWidth(150);    // lock the category list
    m_CategoryList.setMaximumWidth(150);

    m_Splitter.setStretchFactor(0, 0);
    m_Splitter.setStretchFactor(1, 5);
    m_Splitter.setStretchFactor(2, 5);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_Splitter);
}

EmailView::~EmailView()
{
}
