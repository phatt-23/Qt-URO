//
// Created by phatt on 4/25/25.
//

#ifndef ALLMAILLISTVIEW_H
#define ALLMAILLISTVIEW_H


#include "DIContainer.h"
#include "EmailListView.h"


class AllMailListView final : public EmailListView {
public:
    explicit AllMailListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    void ShowEmails(QString const& searchString) override;
private:
};



#endif //ALLMAILLISTVIEW_H
