//
// Created by phatt on 4/8/25.
//

#ifndef SEARCHBAR_H
#define SEARCHBAR_H


#include "DIContainer.h"
#include "EventBus.h"
#include "EmailView/EmailListFilterFrame.h"
#include "EmailView/EmailListSortFrame.h"
#include "QComponent.h"
#include "QtWidgets.h"
#include "StdLib.h"


class EmailListSearchBar final : public QComponent {
    Q_OBJECT
signals:
    void EmailSearchEvent(QString const& searchString);

public:
    explicit EmailListSearchBar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    void BindEvents() override;

    void OnSearchButtonClicked();
    void OnFilterButtonClicked();
    void OnSortButtonClicked();

private:
    Ref<DIContainer> m_DiContainer;

    QLineEdit m_Input;
    QPushButton m_SearchButton;
    QPushButton m_FilterOptionsButton;
    QPushButton m_SortOptionsButton;

    EmailListFilterFrame m_FilterFrame;
    EmailListSortFrame m_SortFrame;
};

#endif //SEARCHBAR_H
