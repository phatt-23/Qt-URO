//
// Created by phatt on 4/26/25.
//

#include "AttachmentSidebarCard.h"

AttachmentSidebarCard::AttachmentSidebarCard(QString const& filepath, QWidget* parent): QComponent("AttachmentSidebarCard", parent)
    , m_FilePath(filepath)
{
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto* filenameLabel = new QLabel(m_FilePath, this);
    filenameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addWidget(filenameLabel);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QWidget::customContextMenuRequested, this, [this](const QPoint& pos)
    {
        QMenu contextMenu;

        const QAction* openAction = contextMenu.addAction("Open");
        connect(openAction, &QAction::triggered, this, [this]()
        {
            auto* attachmentDialog = new AttachmentViewerDialog(m_FilePath, this);
            attachmentDialog->show();
        });

        QAction const* removeAction = contextMenu.addAction("Remove");
        connect(removeAction, &QAction::triggered, this, [this]()
        {
            emit RemoveClicked(this);
        });

        contextMenu.exec(this->mapToGlobal(pos));
    });
}
