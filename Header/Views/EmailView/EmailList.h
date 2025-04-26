//
// Created by phatt on 4/8/25.
//

#ifndef EMAILLIST_H
#define EMAILLIST_H


#include "EmailListFilterFrame.h"
#include "EmailListSearchBar.h"
#include "EmailListSortFrame.h"
#include "QComponent.h"
#include "QtWidgets.h"
#include "EmailListViews/EmailListView.h"


class EmailList final : public QComponent {
    Q_OBJECT
public:
    enum EmailListViews
    {
        INBOX_LIST_VIEW,
        DRAFT_LIST_VIEW,
        SENT_MAIL_LIST_VIEW,
        ALL_MAIL_LIST_VIEW,
        BIN_LIST_VIEW,
        // ...
    };

public:
    explicit EmailList(const Ref<DIContainer>& diContainer, QWidget* parent);

private:
    void HideAllViews() const;
    void BindEvents() override;
    void SetCurrentView(EmailListViews view);

private:
    Ref<DIContainer> m_DiContainer;

    EmailListSearchBar m_SearchBar;

    QMap<EmailListViews, EmailListView*> m_ListViews;
    EmailListViews m_CurrentListView;
};



#endif //EMAILLIST_H
