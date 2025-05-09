#ifndef INCLUDE_EMAILCARDLIST_EMAILCARDLIST_H_
#define INCLUDE_EMAILCARDLIST_EMAILCARDLIST_H_


#include "DIContainer.h"
#include "QComponent.h"
#include "DataModels.h"
#include "QtWidgets.h"


class EmailCardList final : public QComponent
{
    Q_OBJECT
public:
    explicit EmailCardList(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailCardList() override;

    // projects provided emails
    void ProjectEmails(const QList<Email>& emails);


private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QScrollArea m_ScrollArea; 

    // container inside scroll area
    QWidget m_Container;
    QVBoxLayout m_ContainerLayout;
};



#endif  // INCLUDE_EMAILCARDLIST_EMAILCARDLIST_H_
