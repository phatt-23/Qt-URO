//
// Created by phatt on 4/8/25.
//

#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H


#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"


class CategoryList final : public QComponent {
public:
    explicit CategoryList(const Ref<DIContainer>& diContainer, QWidget* parent);

private:
    Ref<DIContainer> m_DiContainer;

    Scope<QAbstractItemView> m_CategoryView;  // necessary indirection
};



#endif //CATEGORYLIST_H
