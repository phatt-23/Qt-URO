//
// Created by phatt on 4/26/25.
//

#include "../Header/Views/ComposeView/EmailEditorHeader.h"

#include "../Header/Database/UserRepo.h"

EmailEditorHeader::EmailEditorHeader(Ref<DIContainer> const& diContainer, QWidget* parent)
    : QComponent("EmailEditorHeader", parent)
    , m_DiContainer(diContainer)
    , m_SenderLineEdit(new QLineEdit(this))
    , m_RecipientsLineEdit(new QLineEdit(this))
    , m_SubjectLineEdit(new QLineEdit(this))
    , m_ContactChooser(new QPushButton("Choose contact", this))
{
    m_SenderLineEdit->setPlaceholderText("Sender...");
    m_RecipientsLineEdit->setPlaceholderText("Recipients...");
    m_SubjectLineEdit->setPlaceholderText("Subject...");

    // header frame
    const auto headerFormLayout = new QFormLayout(this);
    headerFormLayout->setContentsMargins(0, 0, 0, 0);
    headerFormLayout->setSpacing(0);
    headerFormLayout->addRow("Sender", m_SenderLineEdit);

    // recipients line edit with contact chooser
    auto const recipientRow = new QWidget(this);

    auto const recipientRowLayout = new QHBoxLayout(recipientRow);
    recipientRowLayout->setContentsMargins(0, 0, 0, 0);
    recipientRowLayout->setSpacing(0);

    recipientRowLayout->setContentsMargins(0, 0, 0, 0);
    recipientRowLayout->setSpacing(5);

    recipientRowLayout->addWidget(m_RecipientsLineEdit);
    recipientRowLayout->addWidget(m_ContactChooser);

    headerFormLayout->addRow("Recipients", recipientRow);
    headerFormLayout->addRow("Subject", m_SubjectLineEdit);

    BindEvents();
}

void EmailEditorHeader::BindEvents()
{
    connect(m_ContactChooser, &QPushButton::clicked, this, &EmailEditorHeader::ShowContactMenu);
}


void EmailEditorHeader::ShowContactMenu()
{
    const auto users = m_DiContainer->GetService<UserRepo>()->GetAllUsers();

    auto* menu = new QMenu(m_ContactChooser);

    for (const auto& user : users)
    {
        QAction const* action = menu->addAction(user.Email);

        connect(action, &QAction::triggered, this, [this, user]() {
            QString currentText = m_RecipientsLineEdit->text();

            if (!currentText.isEmpty())
            {
                currentText += ", ";
            }

            currentText += user.Email;

            m_RecipientsLineEdit->setText(currentText);
        });
    }

    // Show the menu below the button
    menu->exec(QCursor::pos());
}
