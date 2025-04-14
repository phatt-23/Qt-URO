#ifndef INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_
#define INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_


#include "Database/DataModels.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailCard : public QComponent 
{
public:
    explicit EmailCard(const Email& email, const QString& sender, QWidget* parent = nullptr);
    ~EmailCard() override;

private:
    int m_EmailId;  // personal copy

    QLabel m_SenderLabel;
    QLabel m_SubjectLabel;
    QLabel m_SentAtLabel;
    QPushButton m_PreviewButton;
};


#endif  // INCLUDE_EMAILLISTVIEWS_EMAILCARD_H_


