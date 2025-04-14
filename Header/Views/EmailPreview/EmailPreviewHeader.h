#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWHEADER_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWHEADER_H_



#include "DIContainer.h"
#include "DataModels.h"
#include "QComponent.h"
#include "QtWidgets.h"



class EmailPreviewHeader : public QComponent
{
public:
    EmailPreviewHeader(Ref<DIContainer> const& diContainer, QWidget* parent);
    ~EmailPreviewHeader() override;
   
    void ProjectEmail(Email const& email);

private:
    Ref<DIContainer> m_DiContainer;

    QLabel m_SubjectLabel;
    QLabel m_SenderLabel;
    QLabel m_RecipientsLabel;
};



#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWHEADER_H_


