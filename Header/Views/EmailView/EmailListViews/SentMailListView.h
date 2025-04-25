//
// Created by phatt on 4/25/25.
//

#ifndef SENTMAILLISTVIEW_H
#define SENTMAILLISTVIEW_H
#include "EmailListView.h"


class SentMailListView final : public EmailListView {
public:
    explicit SentMailListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    void ShowEmails(QString const& searchString) override;
private:
};



#endif //SENTMAILLISTVIEW_H
