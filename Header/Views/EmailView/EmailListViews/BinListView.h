//
// Created by phatt on 4/25/25.
//

#ifndef BINLISTVIEW_H
#define BINLISTVIEW_H


#include "EmailListView.h"


class BinListView final : public EmailListView {
    Q_OBJECT
public:
    explicit BinListView(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    void ShowEmails(QString const& searchString) override;

private:
};


#endif //BINLISTVIEW_H
