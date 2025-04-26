//
// Created by phatt on 4/25/25.
//

#include "../Header/Utility/AttachmentViewerDialog.h"

AttachmentViewerDialog::AttachmentViewerDialog(QString const& filepath, QWidget* parent): QDialog(parent)
{
    auto const dialogLayout = new QVBoxLayout(this);
    dialogLayout->setContentsMargins(0, 0, 0, 0);
    dialogLayout->setSpacing(0);


    this->setWindowTitle("Attachment Viewer");
    auto const label = new QLabel("File: " + filepath, this);

    dialogLayout->addWidget(label);

    // HACK:
    // tests if the file can be opened as an image
    if ((QImageReader::imageFormat(filepath)).isEmpty())
    {
        auto const textbox = new QTextEdit(this);

        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly))
            return;

        const QByteArray blob = file.readAll();

        textbox->setText(blob);
        dialogLayout->addWidget(textbox);
    }
    else
    {
        if (QFile file(filepath); !file.open(QIODevice::ReadOnly))
        {
            return;
        }

        QPixmap const pixmap(filepath);

        // Scale the image to fit within the dialog
        auto const pixmapLabel = new QLabel(this);
        pixmapLabel->setPixmap(pixmap.scaled(800, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pixmapLabel->setAlignment(Qt::AlignCenter);

        // Add the image to a scrollable area
        auto const scrollArea = new QScrollArea(this);
        scrollArea->setWidget(pixmapLabel);
        scrollArea->setWidgetResizable(true);

        dialogLayout->addWidget(scrollArea);
    }

    this->resize(600, 400);
}
