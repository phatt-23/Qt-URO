//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailListFilterFrame.h"

#include <QDateEdit>
#include <QCheckBox>

EmailListFilterFrame::EmailListFilterFrame(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailListFilterFrame", parent), m_DiContainer(diContainer)
{
    const auto layout = new QVBoxLayout(this);

    // Filter by Date Range
    auto* dateRangeLabel = new QLabel("Date Range:", this);
    auto* startDateEdit = new QDateEdit(this);
    auto* endDateEdit = new QDateEdit(this);
    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);
    startDateEdit->setDisplayFormat("yyyy-MM-dd");
    endDateEdit->setDisplayFormat("yyyy-MM-dd");

    auto* dateRangeLayout = new QHBoxLayout();
    dateRangeLayout->addWidget(startDateEdit);
    dateRangeLayout->addWidget(new QLabel("to", this), Qt::AlignCenter);
    dateRangeLayout->addWidget(endDateEdit);

    layout->addWidget(dateRangeLabel);
    layout->addLayout(dateRangeLayout);

    // Filter by Recipient
    auto* recipientLabel = new QLabel("Recipient:", this);
    auto* recipientLineEdit = new QLineEdit(this);
    layout->addWidget(recipientLabel);
    layout->addWidget(recipientLineEdit);

    // Filter by Read/Unread Status
    auto* readCheckBox = new QCheckBox("Read", this);
    auto* unreadCheckBox = new QCheckBox("Unread", this);

    auto* readStatusLayout = new QHBoxLayout();
    readStatusLayout->addWidget(readCheckBox);
    readStatusLayout->addWidget(unreadCheckBox);

    layout->addLayout(readStatusLayout);

    // Filter by Attachments
    auto* hasAttachmentCheckBox = new QCheckBox("Has Attachments", this);
    layout->addWidget(hasAttachmentCheckBox);

    // Apply Filters Button
    auto* applyFiltersButton = new QPushButton("Apply Filters", this);
    layout->addWidget(applyFiltersButton);

    // Connect the Apply Filters button to emit an event or handle the filtering logic
    connect(applyFiltersButton, &QPushButton::clicked, this, [this, startDateEdit, endDateEdit, recipientLineEdit, readCheckBox, unreadCheckBox, hasAttachmentCheckBox]() {
        // Gather filter values
        const auto startDate = startDateEdit->date();
        const auto endDate = endDateEdit->date();
        const auto recipient = recipientLineEdit->text();
        const bool isRead = readCheckBox->isChecked();
        const bool isUnread = unreadCheckBox->isChecked();
        const bool hasAttachments = hasAttachmentCheckBox->isChecked();

        // Emit or handle the filtering logic here
        qDebug() << "Filters applied:";
        qDebug() << "Date Range:" << startDate.toString("yyyy-MM-dd") << "to" << endDate.toString("yyyy-MM-dd");
        qDebug() << "Recipient:" << recipient;
        qDebug() << "Read:" << isRead << "Unread:" << isUnread;
        qDebug() << "Has Attachments:" << hasAttachments;
    });
}
