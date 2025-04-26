//
// Created by phatt on 4/25/25.
//

#ifndef ATTACHMENTVIEWERDIALOG_H
#define ATTACHMENTVIEWERDIALOG_H

#include <QImageReader>

#include "QtWidgets.h"

class AttachmentViewerDialog final : public QDialog {
    Q_OBJECT
public:
    explicit AttachmentViewerDialog(QString const& filepath, QWidget* parent = nullptr);

    ~AttachmentViewerDialog() override = default;
};



#endif //ATTACHMENTVIEWERDIALOG_H
