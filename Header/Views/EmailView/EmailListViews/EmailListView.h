//
// Created by phatt on 4/8/25.
//

#ifndef EMAILLISTVIEW_H
#define EMAILLISTVIEW_H


#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"


// abstract
class EmailListView : public QComponent {
public:
    explicit EmailListView(const Ref<DIContainer>& diContainer, const QString& name, QWidget* parent = nullptr);
    ~EmailListView() override;



private:
    Ref<DIContainer> m_DiContainer;
    QScrollArea* m_ScrollArea;
};



#endif //EMAILLISTVIEW_H
