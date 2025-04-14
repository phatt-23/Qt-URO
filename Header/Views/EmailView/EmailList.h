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
#include "EmailListViews/EmailListViews.h"


class EmailList final : public QComponent {
public:
    explicit EmailList(const Ref<DIContainer>& diContainer, QWidget* parent);

private:
    void HideAllViews() const;

private:
    Ref<DIContainer> m_DiContainer;

    EmailListSearchBar m_SearchBar;

    QMap<EmailListViews, EmailListView*> m_ListViews;
    EmailListViews m_CurrentListView;
};



#endif //EMAILLIST_H
