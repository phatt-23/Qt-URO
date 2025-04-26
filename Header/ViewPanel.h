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
#include "EmailView/BaseView.h"


class ViewPanel final : public QComponent {
    Q_OBJECT
public:
    explicit ViewPanel(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    void ShowView(ViewsEnum view);

private slots:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QMap<ViewsEnum, BaseView*> m_Views;
};



#endif //VIEWPANEL_H
