//
// Created by phatt on 4/7/25.
//

#ifndef MENUBAR_H
#define MENUBAR_H

#include "Core.h"


class Menubar final : public QMenuBar {
public:
    explicit Menubar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;
};



#endif //MENUBAR_H
