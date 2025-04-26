//
// Created by phatt on 4/26/25.
//

#include "EmailPreviewAttachmentCard.h"

EmailPreviewAttachmentCard::EmailPreviewAttachmentCard(Attachment const& attachment, QWidget* parent)
    : QComponent("EmailPreviewAttachmentCard", parent)
    , m_FilenameLabel(new QLabel(attachment.FileName, this))
    , m_FilePath(attachment.FileName)
{
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_FilenameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addWidget(m_FilenameLabel);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, [this](const QPoint& pos) {
        QMenu contextMenu;

        const QAction* openAction = contextMenu.addAction("Open");
        connect(openAction, &QAction::triggered, this, [this]() {
            auto* attachmentDialog = new AttachmentViewerDialog(m_FilePath, this);
            attachmentDialog->show();
        });

        contextMenu.exec(this->mapToGlobal(pos));
    });
}
