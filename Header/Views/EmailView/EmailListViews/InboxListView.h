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
    Q_OBJECT
public:
    explicit InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

    void ShowEmails(QString const& searchString) override;

private:
};





#endif //INBOXLISTVIEW_H
