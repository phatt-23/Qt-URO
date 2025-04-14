//
// Created by phatt on 4/8/25.
//

#include "InboxListView.h"

#include "EmailCardList.h"
#include "EmailEditor.h"
#include "Database/EmailRepo.h"
#include "Utility.h"
#include "Database/UserRepo.h"
#include "QtWidgets.h"
#include "EmailCard.h"



InboxListView::InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "InboxListView", parent)
{
    // TODO : load from db (remove later)
    const auto emailRepo = diContainer->GetService<EmailRepo>();
    const auto userRepo = diContainer->GetService<UserRepo>();


    const auto emails = emailRepo->GetAllEmails();
    m_EmailCardList.ProjectEmails(emails);



    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_EmailCardList);


    // const auto bus = m_DiContainer->GetService<EventBus>();
    // bus->Subscribe<EmailWrittenEvent>([this](const auto& e) {
    //     const EmailEditor::DataContext* data = e.m_Data;
    //
    //     const QList<QStandardItem*> row = {
    //         new QStandardItem(data->SenderLideEdit.text()),
    //         new QStandardItem(data->RecipientsLideEdit.text()),
    //         new QStandardItem(data->SubjectLideEdit.text()),
    //         new QStandardItem(data->TextBody.toPlainText()),
    //     };
    //
    //     m_ItemModel.appendRow(row);
    // });
}


