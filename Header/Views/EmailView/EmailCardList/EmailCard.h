#ifndef INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_
#define INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_


#include "DIContainer.h"
#include "Database/DataModels.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailCard : public QComponent 
{
public:
    explicit EmailCard(Ref<DIContainer> const& diContainer, const Email& email, const QString& sender, QWidget* parent = nullptr);
    ~EmailCard() override;

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    int m_EmailId;  // personal copy

    QLabel m_SenderLabel;
    QLabel m_SubjectLabel;
    QLabel m_SentAtLabel;
    QPushButton m_PreviewButton;
};


// Event
struct PreviewEmailClicked : public EventBase
{
    PreviewEmailClicked(int emailId) : EmailId(emailId) {}
    int EmailId;
};


inline QDebug operator<<(QDebug dbg, PreviewEmailClicked const& e)
{
    dbg.nospace() << "PreviewEmailClicked(email_id: " << e.EmailId << ")";
    return dbg;
}


#endif  // INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_


