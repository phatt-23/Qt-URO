//
// Created by phatt on 4/7/25.
//

#include "../Header/Menubar.h"

Menubar::Menubar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QMenuBar(parent)
    , m_DiContainer(diContainer)
{
    const auto fileMenu = this->addMenu("File");
    fileMenu->addAction("Compose");
    fileMenu->addAction("Quit");

}
