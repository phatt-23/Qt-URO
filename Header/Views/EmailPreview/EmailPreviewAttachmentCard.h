//
// Created by phatt on 4/26/25.
//

#ifndef EMAILPREVIEWATTACHMENTCARD_H
#define EMAILPREVIEWATTACHMENTCARD_H
#include "AttachmentViewerDialog.h"
#include "DataModels.h"
#include "QComponent.h"
#include "QtWidgets.h"

class EmailPreviewAttachmentCard final : public QComponent
{
    Q_OBJECT
public:
    EmailPreviewAttachmentCard(Attachment const& attachment, QWidget* parent);

    ~EmailPreviewAttachmentCard() override {}

private:
    QLabel* m_FilenameLabel;
    QString m_FilePath;
};



#endif //EMAILPREVIEWATTACHMENTCARD_H
