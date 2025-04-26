//
// Created by phatt on 4/8/25.
//

#include "EmailEditor.h"

#include "Config.h"
#include "EmailEditorBody.h"
#include "UserRepo.h"

EmailEditor::EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailEditor", parent), m_DiContainer(diContainer)
    // init children
    , m_Toolbar(new EmailEditorToolbar(diContainer, this))
    , m_Header(new EmailEditorHeader(diContainer, this))
    , m_Body(new EmailEditorBody(this))
{
    // layout children
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_Toolbar);
    layout->addWidget(m_Header);
    layout->addWidget(m_Body);
    layout->setStretch(0, 0);   // Toolbar
    layout->setStretch(1, 0);   // Header
    layout->setStretch(2, 4);   // Body

    // set default email
    m_Header->m_SenderLineEdit->setReadOnly(true);
    m_Header->m_SenderLineEdit->setText(DEFAULT_EMAIL_ADDRESS);

    // events
    BindEvents();
}

EmailEditor::~EmailEditor()
{
}

bool IsValidEmail(QString const& email)
{
    const QRegularExpression regex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    return regex.match(email).hasMatch();
}

void EmailEditor::BindEvents()
{
    auto bus = this->m_DiContainer->GetService<EventBus>();

    connect(m_Toolbar, &EmailEditorToolbar::SendButtonClicked, this, [this, bus]()
    {
        auto recipients = m_Header->m_RecipientsLineEdit->text().split(',', Qt::SkipEmptyParts);

        for (const auto& recipient : recipients) {
            if (!IsValidEmail(recipient.trimmed())) {
                m_Header->m_RecipientsLineEdit->setStyleSheet("border: 2px solid red;");
                QMessageBox::warning(this, "Invalid Email", "One or more recipient email addresses are invalid.");
                return;
            }
            else
            {
                m_Header->m_RecipientsLineEdit->setStyleSheet("");
            }
        }

        bus->ForwardEmit<SendEmailClickedEvent>(GetDataContext());
    });

    connect(m_Toolbar, &EmailEditorToolbar::SaveButtonClicked, this, [this, bus] {
        bus->ForwardEmit<SaveEmailClickedEvent>(GetDataContext());
    });

    connect(m_Toolbar, &EmailEditorToolbar::AttachButtonClicked, this, [this, bus] {
        const auto dialog = new QFileDialog(this);
        const auto files = dialog->getOpenFileNames(this, "Choose attachments");

        bus->ForwardEmit<AttachToEmailEvent>(files);
    });
}

