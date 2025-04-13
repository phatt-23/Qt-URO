//
// Created by phatt on 4/7/25.
//

#ifndef VIEWPANEL_H
#define VIEWPANEL_H
#include <QWidget>

#include "DIContainer.h"
#include "Events.h"
#include "QComponent.h"
#include "SideBar.h"
#include "Core/StdLib.h"


class ViewPanel final : public QComponent {
public:
    explicit ViewPanel(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private slots:
    void onSideBarButtonClicked(const SideBarButtonClickedEvent& event);

private:
    Ref<DIContainer> m_DiContainer;

    QMap<ViewsEnum, QWidget*> m_Views;
};



#endif //VIEWPANEL_H
