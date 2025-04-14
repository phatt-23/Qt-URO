//
// Created by phatt on 4/8/25.
//

#ifndef EMAILLISTVIEW_H
#define EMAILLISTVIEW_H


#include "DIContainer.h"
#include "EmailCardList.h"
#include "QComponent.h"
#include "QtWidgets.h"


// abstract
class EmailListView : public QComponent {
public:
    explicit EmailListView(const Ref<DIContainer>& diContainer, const QString& name, QWidget* parent = nullptr);
    ~EmailListView() override;

protected:
    Ref<DIContainer> m_DiContainer;
    EmailCardList m_EmailCardList;
};



#endif //EMAILLISTVIEW_H
