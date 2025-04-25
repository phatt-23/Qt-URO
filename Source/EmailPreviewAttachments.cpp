
#include "EmailPreviewAttachments.h"

#include <QImageReader>

#include "AttachmentRepo.h"
#include "AttachmentViewerDialog.h"
#include "EmailCard.h"
#include "EmailRepo.h"



class EmailPreviewAttachmentCard final : public QComponent
{
public:  
    EmailPreviewAttachmentCard(Attachment const& attachment, QWidget* parent)
        : QComponent("EmailPreviewAttachmentCard", parent)
        , m_FilenameLabel(new QLabel(attachment.FileName, this))
        , m_FilePath(attachment.FileName)
    {
        auto const layout = new QHBoxLayout(this);    

        auto const openButton = new QPushButton("Open");

        layout->addWidget(m_FilenameLabel);
        layout->addStretch();
        layout->addWidget(openButton);

        connect(openButton, &QPushButton::clicked, [this]
        {
            const auto dialog = new AttachmentViewerDialog(m_FilePath, this);
            dialog->show();
        });
    }

    ~EmailPreviewAttachmentCard() override {}

private:
    QLabel* m_FilenameLabel;
    QString m_FilePath;
};



EmailPreviewAttachments::EmailPreviewAttachments(Ref<DIContainer> const& diContainer, QWidget* parent)
    : QComponent("EmailPreviewAttachments", parent)
    , m_DiContainer(diContainer)
    , m_ScrollArea(new QScrollArea(this))
    , m_Container(new QWidget())
    , m_ContainerLayout(new QVBoxLayout(m_Container))
{
    m_ScrollArea->setWidgetResizable(true);
    m_ScrollArea->setWidget(m_Container);

    auto const& layout = new QVBoxLayout(this);
    layout->addWidget(m_ScrollArea);

    m_ContainerLayout->setAlignment(Qt::AlignTop);

    BindEvents();
}

EmailPreviewAttachments::~EmailPreviewAttachments() 
{
}

void EmailPreviewAttachments::BindEvents()
{
}

void EmailPreviewAttachments::ProjectEmail(int const emailId)
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    auto const attachments = m_DiContainer->GetService<AttachmentRepo>()->GetAttachments(emailId);

    if (attachments.length() == 0)
    {
        this->hide();
        return;
    }


    this->show();

    for (auto const& attch : attachments)
    {
        qInfo() << "Show this:" << attch;
    }

    // kill all children
    auto children = m_Container->children();
    for (auto* ch : children)
    {
        if (auto* child = qobject_cast<QWidget*>(ch)) 
        {
            m_ContainerLayout->removeWidget(child);
            child->deleteLater();
        }
    }

    // populate
    for (const auto& attachment : attachments)
    {
        // m_ContainerLayout->addWidget(new QPushButton(attachment.FileName, this));
        const auto attachmentCard = new EmailPreviewAttachmentCard(attachment, m_Container);
        attachmentCard->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_ContainerLayout->addWidget(attachmentCard);
    }

    m_Container->setLayout(m_ContainerLayout);
    m_ContainerLayout->update();
}

void EmailPreviewAttachments::Clear() const
{
    // kill all children
    auto children = m_Container->children();
    for (auto* ch : children)
    {
        if (auto* child = qobject_cast<QWidget*>(ch))
        {
            m_ContainerLayout->removeWidget(child);
            child->deleteLater();
        }
    }
}
