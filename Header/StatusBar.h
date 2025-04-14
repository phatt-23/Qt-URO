//
// Created by phatt on 4/7/25.
//

#ifndef STATUSBAR_H
#define STATUSBAR_H


#include "Core/QtWidgets.h"
#include "Core/StdLib.h"


class DIContainer;

class StatusBar final : public QStatusBar {
public:
    explicit StatusBar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;
};



#endif //STATUSBAR_H
