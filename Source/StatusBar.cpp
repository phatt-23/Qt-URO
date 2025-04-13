//
// Created by phatt on 4/7/25.
//

#include "../Header/StatusBar.h"

StatusBar::StatusBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QStatusBar(parent), m_DiContainer(diContainer)
{
    this->showMessage("TRA0163");

}
