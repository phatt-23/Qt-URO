//
// Created by phatt on 4/8/25.
//

#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H


#include "DIContainer.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"


class CategoryList final : public QComponent {
    Q_OBJECT
public:
    enum CategoryListButton
    {
        INBOX,
        DRAFTS,
        SENT_MAIL,
        ALL_MAIL,
        BIN,
        SPAM,
        IMPORTANT,
        STARRED,
    };

public:
    explicit CategoryList(const Ref<DIContainer>& diContainer, QWidget* parent);

private:
    void BindEvents() override;
    void SetLastClickedButton(CategoryListButton const button);

private:
    Ref<DIContainer> m_DiContainer;

    QScrollArea m_ScrollArea;

    // container inside scroll area
    QWidget m_Container;
    QVBoxLayout m_ContainerLayout;

    QMap<CategoryListButton, QPushButton*> m_Buttons;

    QPushButton* m_LastClickedButton;
};


struct InboxItemClickedEvent final : EventBase
{

};

struct DraftsItemClickedEvent final : EventBase
{

};

struct SentMailItemClickedEvent final : EventBase
{

};

struct AllMailItemClickedEvent final : EventBase
{

};

struct SpamItemClickedEvent final : EventBase
{

};

struct BinItemClickedEvent final : EventBase
{

};

struct ImportantItemClickedEvent final : EventBase
{

};

struct StarredItemClickedEvent final : EventBase
{

};


#endif //CATEGORYLIST_H
