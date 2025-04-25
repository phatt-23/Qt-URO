//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/ComposeView.h"

#include "EmailEditor.h"
#include "FormInserter.h"
#include "UserRepo.h"


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
    layout->addWidget(m_Splitter);

    // left split
    const auto leftSplitLayout = new QVBoxLayout(m_LeftSplit);
    leftSplitLayout->addWidget(m_EmailEditor);

    if (m_IsDialog == false)
    {
        m_OpenInNewButton = new QPushButton("Open in New", m_LeftSplit);
        const auto buttonLayout = new QHBoxLayout();
        leftSplitLayout->addLayout(buttonLayout);
        buttonLayout->addStretch();
        buttonLayout->addWidget(m_OpenInNewButton);
    }

    leftSplitLayout->setStretch(0, 4);
    leftSplitLayout->setStretch(1, 0);

    // right split
    const auto rightSplitLayout = new QVBoxLayout(m_RightSplit);
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
    
    bus->Subscribe<SendEmailClickedEvent>([this](SendEmailClickedEvent const& e) 
    {
        auto const attachmentFiles = m_AttachmentSideBar->GetAttachments(); 
        auto const& emailData = m_EmailEditor->GetDataContext();

        // validate input
        QStringList errorMessages;


        if (emailData.SenderLineEdit.text().isEmpty())
            errorMessages.append("Senders can't be empty.");

        if (emailData.RecipientsLideEdit.text().isEmpty())
            errorMessages.append("Recipients can't be empty.");

        if (emailData.SubjectLineEdit.text().isEmpty())
            errorMessages.append("Subjects can't be empty.");

        if (emailData.TextBody.toPlainText().isEmpty())
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
                .SenderId = userRepo->GetUser(emailData.SenderLineEdit.text()).UserId,
                .Subject = emailData.SubjectLineEdit.text(),
                .Body = emailData.TextBody.toPlainText(),
            };

            inserter->InsertEmailWithAttachments(email, attachmentFiles);
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
                .SenderId = userRepo->GetUser(emailData.SenderLineEdit.text()).UserId,
                .Subject = emailData.SubjectLineEdit.text(),
                .Body = emailData.TextBody.toPlainText(),
            };

            inserter->InsertEmailWithAttachments(email, attachmentFiles, EmailStatus::DRAFT);
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
        context.RecipientsLideEdit.text(),
        context.SubjectLineEdit.text(),
        context.TextBody.toPlainText(),
        m_AttachmentSideBar->GetAttachments());

    const auto dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->addWidget(composeView);

    dialog->show();
    
    connect(dialog, &QDialog::done, this, [this]() {
        m_EmailEditor->SetReadonly(false);
        m_AttachmentSideBar->SetReadonly(false);
    });
}

