//
// Created by phatt on 4/7/25.
//

#ifndef CONTACTS_VIEW_H
#define CONTACTS_VIEW_H


#include "Core.h"
#include "QComponent.h"


class ContactsView final : public QComponent {

public:
    explicit ContactsView(const Ref<DIContainer>& diContainer, QWidget* parent);
    ~ContactsView() override;

private:
    Ref<DIContainer> m_DiContainer;

    QAbstractItemView* m_ContactsView;
    QStandardItemModel* m_ContactsModel;
};



#endif //CONTACTS_VIEW_H
