//
// Created by phatt on 4/25/25.
//

#ifndef DRAFTSLISTVIEW_H
#define DRAFTSLISTVIEW_H


#include "DIContainer.h"
#include "EmailListView.h"


class DraftsListView final : public EmailListView {
    Q_OBJECT
public:
    explicit DraftsListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    void ShowEmails(QString const& searchString) override;

private:
};



#endif //DRAFTSLISTVIEW_H
