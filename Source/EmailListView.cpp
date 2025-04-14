//
// Created by phatt on 4/8/25.
//

#include "EmailListView.h"

EmailListView::EmailListView(const Ref<DIContainer>& diContainer, const QString& name, QWidget* parent)
    : QComponent(name, parent)
    , m_DiContainer(diContainer)
    , m_EmailCardList(m_DiContainer, this)
{
}

EmailListView::~EmailListView()
{
}
