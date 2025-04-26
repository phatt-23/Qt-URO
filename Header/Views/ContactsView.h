//
// Created by phatt on 4/7/25.
//

#ifndef CONTACTS_VIEW_H
#define CONTACTS_VIEW_H


#include "Core.h"
#include "EmailView/BaseView.h"


class ContactsView final : public BaseView {
    Q_OBJECT
public:
    explicit ContactsView(const Ref<DIContainer>& diContainer, QWidget* parent);
    ~ContactsView() override;

    void OnEnter() override;

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QAbstractItemView* m_ContactsView;
    QStandardItemModel* m_ContactsModel;

    QScrollArea* m_ScrollArea;
    QWidget* m_ContainerWidget;
    QVBoxLayout* m_ContainerLayout;

    QPushButton* m_AddNewContactButton;
};



#endif //CONTACTS_VIEW_H
