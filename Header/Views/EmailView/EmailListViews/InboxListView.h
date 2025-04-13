//
// Created by phatt on 4/8/25.
//

#ifndef INBOXLISTVIEW_H
#define INBOXLISTVIEW_H


#include "EmailEditor.h"
#include "EmailListView.h"



class InboxListView final : public EmailListView {
public:
    explicit InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    void OnEmailWrittenEvent(const EmailWrittenEvent& event);

private:
    Ref<DIContainer> m_DiContainer;
    QStandardItemModel m_ItemModel;
};





#endif //INBOXLISTVIEW_H
