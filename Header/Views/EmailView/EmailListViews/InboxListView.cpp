//
// Created by phatt on 4/8/25.
//

#include "InboxListView.h"

#include "EmailEditor.h"
#include "Database/EmailRepo.h"
#include "Utility.h"
#include "Database/UserRepo.h"

InboxListView::InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "InboxListView", parent), m_DiContainer(diContainer)
    , m_ItemModel(0, 4, this)
{
    // create view
    const auto tableView = new QTableView(this);

    // represents model (data)
    tableView->setModel(&m_ItemModel);


    // columns
    m_ItemModel.setHeaderData(0, Qt::Horizontal, QString("Sender"));
    m_ItemModel.setHeaderData(1, Qt::Horizontal, QString("Recipients"));
    m_ItemModel.setHeaderData(2, Qt::Horizontal, QString("Subject"));
    m_ItemModel.setHeaderData(3, Qt::Horizontal, QString("Body"));


    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(tableView);



    // TODO : load from db (remove later)
    const auto emailRepo = diContainer->GetService<EmailRepo>();
    const auto emails = emailRepo->GetAllEmails();


    const auto userRepo = diContainer->GetService<UserRepo>();

    qInfo() << "BEGIN Emails ------------------------------";
    for (const auto& email : emails)
    {
        qInfo() << email;

        const auto recipients = userRepo->GetRecipients(email.EmailId);

        qInfo() << "# of recipients:" << recipients.count();

        QString recipientsConcat;
        for (const auto& recipient : recipients)
        {
            qInfo() << "Recipient:" << recipient;
            recipientsConcat += recipient.Email + ", ";
        }

        const auto row = CreateRow({
            userRepo->GetUser(email.SenderId).Email,
            recipientsConcat,
            email.Subject,
            email.Body,
        });

        m_ItemModel.appendRow(row);
    }
    qInfo() << "END Emails ------------------------------";

    // email card
    const auto Card = new QGroupBox("card");
    const auto cardLayout = new QHBoxLayout();



    // cardLayout-
    // Card
    // layout->addWidget(new)


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

void InboxListView::OnEmailWrittenEvent(const EmailWrittenEvent& event)
{
}

