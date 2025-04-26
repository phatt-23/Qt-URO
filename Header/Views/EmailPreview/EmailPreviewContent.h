#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_




#include "DIContainer.h"
#include "DataModels.h"
#include "EmailPreviewHeader.h"
#include "EmailPreviewBody.h"
#include "EmailPreviewAttachments.h"
#include "QComponent.h"



class EmailPreviewContent final : public QComponent
{
    Q_OBJECT
public:
    friend class EmailPreview;
public:
    explicit EmailPreviewContent(const Ref<DIContainer>& diContainer, QWidget* parent);
    ~EmailPreviewContent() override;

    void ShowEmail(Email const& email);
    void HideEmail();

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    std::optional<Email> m_Email;
    QSplitter m_Splitter;  // vertical splitter for body and attachments

    EmailPreviewHeader m_Header;
    EmailPreviewBody m_Body;
    EmailPreviewAttachments m_Attachments;
};




#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_
