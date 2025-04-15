#include "EmailPreviewAttachments.h"
#include "AttachmentRepo.h"



class EmailPreviewAttachmentCard final : public QComponent
{
public:  
    EmailPreviewAttachmentCard(Attachment const& attachment, QWidget* parent)
        : QComponent("EmailPreviewAttachmentCard", parent)
        , m_FilenameLabel(attachment.FileName, this)
    {
        auto const layout = new QHBoxLayout(this);    
        layout->addWidget(&m_FilenameLabel);
    }

private:
    QLabel m_FilenameLabel;
};



EmailPreviewAttachments::EmailPreviewAttachments(Ref<DIContainer> const& diContainer, QWidget* parent)
    : QComponent("EmailPreviewAttachments", parent)
    , m_DiContainer(diContainer)
    , m_ScrollArea(this)
    , m_Container()
    , m_ContainerLayout(&m_Container)
{
    m_ScrollArea.setWidget(&m_Container);

    auto const& layout = new QVBoxLayout(this);
    layout->addWidget(&m_ScrollArea);
}

EmailPreviewAttachments::~EmailPreviewAttachments() 
{
}

void EmailPreviewAttachments::ProjectEmail(Email const& email)
{
    auto const attachmentRepo = m_DiContainer->GetService<AttachmentRepo>();
    auto const attachments = attachmentRepo->GetAttachments(email.EmailId);

    for (auto const& attch : attachments)
    {
        qInfo() << "Show this:" << attch;
    }

    // kill all children
    auto children = m_Container.children();
    for (auto* ch : children)
    {
        auto child = qobject_cast<QWidget*>(ch);
        if (child != nullptr) 
            m_ContainerLayout.removeWidget(child);
    }

    // populate
    for (const auto& attachment : attachments)
    {
        m_ContainerLayout.addWidget(new EmailPreviewAttachmentCard(attachment, &m_Container));
    }
}
