#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWHEADER_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWHEADER_H_



#include "DIContainer.h"
#include "DataModels.h"
#include "QComponent.h"
#include "QtWidgets.h"



class EmailPreviewHeader : public QComponent
{
    Q_OBJECT
public:
    EmailPreviewHeader(Ref<DIContainer> const& diContainer, QWidget* parent);
    ~EmailPreviewHeader() override;
   
    void ProjectEmail(Email const& email);
    void Clear() const;

private:
    Ref<DIContainer> m_DiContainer;

    QLabel* m_SubjectValueLabel;
    QLabel* m_SenderLabel;
    QLabel* m_SenderValueLabel;
    QLabel* m_RecipientsLabel;
    QLabel* m_RecipientsValueLabel;
};



#endif


