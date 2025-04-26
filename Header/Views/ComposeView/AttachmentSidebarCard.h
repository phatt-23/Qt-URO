//
// Created by phatt on 4/26/25.
//

#ifndef ATTACHMENTSIDEBARCARD_H
#define ATTACHMENTSIDEBARCARD_H

#include "AttachmentViewerDialog.h"
#include "QComponent.h"
#include "QtWidgets.h"


class AttachmentSidebarCard final : public QComponent {
    Q_OBJECT
signals:
    void RemoveClicked(AttachmentSidebarCard*);

public:
    explicit AttachmentSidebarCard(QString const& filepath, QWidget* parent);

private:
    QString m_FilePath;
};



#endif //ATTACHMENTSIDEBARCARD_H
