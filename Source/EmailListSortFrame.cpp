//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailListSortFrame.h"

EmailListSortFrame::EmailListSortFrame(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailListSortFrame", parent), m_DiContainer(diContainer)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    auto ascending = new QRadioButton(tr("Ascending"), this);
    auto descending = new QRadioButton(tr("Descending"), this);

    layout->addWidget(ascending);
    layout->addWidget(descending);
}
