//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/EmailListFilterFrame.h"

#include <QDateEdit>
#include <QCheckBox>

#include "CreateKeyValueRow.h"

EmailListFilterFrame::EmailListFilterFrame(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailListFilterFrame", parent), m_DiContainer(diContainer)
{
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Filter by Date Range
    m_DateRangeLabel = new QLabel("Date Range:", this);

    m_StartDateEdit = new QDateEdit(this);
    m_EndDateEdit = new QDateEdit(this);

    m_StartDateEdit->setCalendarPopup(true);
    m_EndDateEdit->setCalendarPopup(true);
    m_StartDateEdit->setDisplayFormat("yyyy-MM-dd");
    m_EndDateEdit->setDisplayFormat("yyyy-MM-dd");

    m_DateRangeLayout = new QHBoxLayout();

    m_DateRangeLayout->addLayout(CreateKeyValueRow("Start:", m_StartDateEdit, this));
    m_DateRangeLayout->addStretch();
    m_DateRangeLayout->addLayout(CreateKeyValueRow("End:", m_EndDateEdit, this));

    layout->addWidget(m_DateRangeLabel);
    layout->addLayout(m_DateRangeLayout);

    // Filter by Recipient
    m_RecipientLabel = new QLabel("Recipient:", this);
    m_RecipientLineEdit = new QLineEdit(this);
    m_RecipientLineEdit->setPlaceholderText("Recipient...");
    layout->addWidget(m_RecipientLabel);
    layout->addWidget(m_RecipientLineEdit);

    // Filter by Read/Unread Status
    m_ReadCheckBox = new QCheckBox("Read", this);
    m_UnreadCheckBox = new QCheckBox("Unread", this);

    m_ReadStatusLayout = new QHBoxLayout();
    m_ReadStatusLayout->addWidget(m_ReadCheckBox);
    m_ReadStatusLayout->addWidget(m_UnreadCheckBox);

    layout->addLayout(m_ReadStatusLayout);

    // Filter by Attachments
    m_HasAttachmentCheckBox = new QCheckBox("Has Attachments", this);
    layout->addWidget(m_HasAttachmentCheckBox);

    // Apply Filters Button
    m_ApplyFiltersButton = new QPushButton("Apply Filters", this);
    m_ApplyFiltersButtonLayout = new QHBoxLayout();
    m_ApplyFiltersButtonLayout->addStretch();
    m_ApplyFiltersButtonLayout->addWidget(m_ApplyFiltersButton);

    layout->addLayout(m_ApplyFiltersButtonLayout);

    // connect(applyFiltersButton, &QPushButton::clicked, this, [this, startDateEdit, endDateEdit, recipientLineEdit, readCheckBox, unreadCheckBox, hasAttachmentCheckBox]() {
    //     const auto startDate = startDateEdit->date();
    //     const auto endDate = endDateEdit->date();
    //     const auto recipient = recipientLineEdit->text();
    //     const bool isRead = readCheckBox->isChecked();
    //     const bool isUnread = unreadCheckBox->isChecked();
    //     const bool hasAttachments = hasAttachmentCheckBox->isChecked();
    //
    //     qDebug() << "Filters applied:";
    //     qDebug() << "Date Range:" << startDate.toString("yyyy-MM-dd") << "to" << endDate.toString("yyyy-MM-dd");
    //     qDebug() << "Recipient:" << recipient;
    //     qDebug() << "Read:" << isRead << "Unread:" << isUnread;
    //     qDebug() << "Has Attachments:" << hasAttachments;
    // });
}
