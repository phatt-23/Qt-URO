//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/ComposeView.h"

#include "AttachmentRepo.h"
#include "EmailEditor.h"
#include "EmailRepo.h"
#include "FormInserter.h"
#include "UserRepo.h"
#include "EmailView/EmailPreview.h"


ComposeView::ComposeView(const Ref<DIContainer>& diContainer, QWidget* parent, const bool isDialog)
    : BaseView("ComposeView", parent)
    , m_DiContainer(diContainer)
    // init children
    , m_Splitter(new QSplitter(Qt::Horizontal, this))
    , m_LeftSplit(new QComponent("LeftSplit", this))
    , m_RightSplit(new QComponent("RightSplit", this))
    , m_EmailEditor(new EmailEditor(m_DiContainer, m_LeftSplit))
    , m_AttachmentSideBar(new AttachmentSideBar(m_DiContainer, m_RightSplit))
    , m_IsDialog(isDialog)
{
    // split widgets
    m_Splitter->addWidget(m_LeftSplit);
    m_Splitter->addWidget(m_RightSplit);

    m_Splitter->setSizes({400, 200});
    m_Splitter->setStretchFactor(0, 4);
    m_Splitter->setStretchFactor(1, 3);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_Splitter);

    // left split
    const auto leftSplitLayout = new QVBoxLayout(m_LeftSplit);
    leftSplitLayout->setContentsMargins(0, 0, 0, 0);
    leftSplitLayout->setSpacing(0);

    leftSplitLayout->addWidget(m_EmailEditor);

    if (m_IsDialog == false)
    {
        m_OpenInNewButton = new QPushButton("Open in New", m_LeftSplit);
        m_OpenInNewButton->setProperty("class", "open-in-new");
        const auto buttonLayout = new QHBoxLayout();
        leftSplitLayout->addLayout(buttonLayout);
        buttonLayout->addStretch();
        buttonLayout->addWidget(m_OpenInNewButton);
    }

    leftSplitLayout->setStretch(0, 4);
    leftSplitLayout->setStretch(1, 0);

    // right split
    const auto rightSplitLayout = new QVBoxLayout(m_RightSplit);
    rightSplitLayout->setContentsMargins(0, 0, 0, 0);
    rightSplitLayout->setSpacing(0);

    rightSplitLayout->addWidget(m_AttachmentSideBar);

    // events
    BindEvents();
}

void ComposeView::ClearContent() const
{
    m_EmailEditor->ClearEntries();
    m_AttachmentSideBar->Clear();
}

void ComposeView::SetContent(QString const& recipients, QString const& subject, QString const& body,
    QStringList const& attachments) const
{
    m_EmailEditor->SetEntries(recipients, subject, body);
    m_AttachmentSideBar->SetList(attachments);
}


void ComposeView::OnEnter()
{

}


void ComposeView::BindEvents()
{
    connect(m_OpenInNewButton, &QPushButton::clicked, this, &ComposeView::OpenInNewButtonClicked);

    auto const bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<EditButtonClickedEvent>([this](EditButtonClickedEvent const& e)
    {
        const auto email = m_DiContainer->GetService<EmailRepo>()->GetEmail(e.EmailId);
        auto recipients = m_DiContainer->GetService<UserRepo>()->GetRecipients(e.EmailId);
        auto attachments = m_DiContainer->GetService<AttachmentRepo>()->GetAttachments(e.EmailId);

        QStringList recipientEmails;
        for (const auto& r : recipients)
        {
            recipientEmails.append(r.Email);
        }

        QStringList attachmentFiles;
        for (const auto& a : attachments)
        {
            attachmentFiles.append(a.FilePath);
        }

        m_EmailEditor->SetEntries(recipientEmails.join(","), email.Subject, email.Body);
        m_AttachmentSideBar->SetList(attachmentFiles);
    });

    bus->Subscribe<SendEmailClickedEvent>([this](SendEmailClickedEvent const& e) 
    {
        auto const attachmentFiles = m_AttachmentSideBar->GetAttachments();
        auto const& emailData = m_EmailEditor->GetDataContext();

        // validate input
        QStringList errorMessages;


        if (emailData.Sender.isEmpty())
            errorMessages.append("Senders can't be empty.");

        if (emailData.Recipients.isEmpty())
            errorMessages.append("Recipients can't be empty.");

        if (emailData.Subject.isEmpty())
            errorMessages.append("Subjects can't be empty.");

        if (emailData.Body.isEmpty())
            errorMessages.append("Body can't be empty.");

        if (!errorMessages.empty())
        {
            QMessageBox::warning(this, "Invalid email", errorMessages.join("\n"));
            return;
        }

        qInfo() << "Insert new email" << emailData << attachmentFiles;

        auto const inserter = m_DiContainer->GetService<FormInserter>();
        auto const userRepo = m_DiContainer->GetService<UserRepo>();

        try
        {
            Email const email = {
                .SenderId = userRepo->GetUser(emailData.Sender).UserId,
                .Subject = emailData.Subject,
                .Body = emailData.Body,
            };

            if (!inserter->InsertEmailWithAttachments(email, emailData.Recipients, attachmentFiles))
            {
                return;
            }

            ClearContent();
        }
        catch (std::exception const& ex)
        {
            qCritical() << "Error:" << ex.what();
            return;
        }
    });

    bus->Subscribe<SaveEmailClickedEvent>([this](SaveEmailClickedEvent const& e)
    {
        auto const attachmentFiles = m_AttachmentSideBar->GetAttachments();
        auto const& emailData = m_EmailEditor->GetDataContext();

        auto const inserter = m_DiContainer->GetService<FormInserter>();
        auto const userRepo = m_DiContainer->GetService<UserRepo>();

        try
        {
            Email const email = {
                .SenderId = userRepo->GetUser(emailData.Sender).UserId,
                .Subject = emailData.Subject,
                .Body = emailData.Body,
            };

            if (!inserter->InsertEmailWithAttachments(email, emailData.Recipients, attachmentFiles))
            {
                return;
            }

            ClearContent();
        }
        catch (std::exception const& ex)
        {
            qCritical() << "Error:" << ex.what();
            return;
        }
    });
}

void ComposeView::OpenInNewButtonClicked()
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    m_EmailEditor->SetReadonly(true);
    m_AttachmentSideBar->SetReadonly(true);

    const auto dialog = new QDialog(this);
    dialog->setWindowTitle("Compose Email");
    dialog->resize(800, 600);

    auto composeView = new ComposeView(m_DiContainer, this, true);

    const auto& context = m_EmailEditor->GetDataContext();
    composeView->SetContent(
        context.Recipients.join(","),
        context.Subject,
        context.Body,
        m_AttachmentSideBar->GetAttachments());

    const auto dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->setContentsMargins(0, 0, 0, 0);
    dialogLayout->setSpacing(0);

    dialogLayout->addWidget(composeView);

    dialog->show();
    
    connect(dialog, &QDialog::done, this, [this]() {
        m_EmailEditor->SetReadonly(false);
        m_AttachmentSideBar->SetReadonly(false);
    });
}

