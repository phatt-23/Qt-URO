//
// Created by phatt on 4/8/25.
//

#ifndef INBOXLISTVIEW_H
#define INBOXLISTVIEW_H


#include "EmailCardList.h"
#include "EmailEditor.h"
#include "EmailListView.h"
#include "Core.h"


class InboxListView final : public EmailListView {
public:
    explicit InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:

private:
};





#endif //INBOXLISTVIEW_H
