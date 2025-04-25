//
// Created by phatt on 4/8/25.
//

#include "EmailEditor.h"

#include <qcombobox.h>

#include "UserRepo.h"

EmailEditor::EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailEditor", parent), m_DiContainer(diContainer)
    // init children
    , m_ToolbarFrame("ToolbarFrame", this)
    , m_HeaderFrame("HeaderFrame", this)
    , m_BodyFrame("BodyFrame", this)
    , m_Data(CreateScope<DataContext>(this))  // data context
    , m_ContactChooser(new QPushButton("Choose contact", this)) // Replace QComboBox with QPushButton
{
    // layout children
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_ToolbarFrame);
    layout->addWidget(&m_HeaderFrame);
    layout->addWidget(&m_BodyFrame);
    layout->setStretch(0, 0);   // Toolbar
    layout->setStretch(1, 0);   // Header
    layout->setStretch(2, 4);   // Body


    // toolbar frame
    m_ToolbarButtons[SEND] = new QPushButton("Send", &m_ToolbarFrame);
    m_ToolbarButtons[SAVE] = new QPushButton("Save", &m_ToolbarFrame);
    m_ToolbarButtons[ATTACH] = new QPushButton("Attach", &m_ToolbarFrame);

    const auto toolbarLayout = new QHBoxLayout(&m_ToolbarFrame);
    toolbarLayout->addWidget(m_ToolbarButtons[SEND]);
    toolbarLayout->addWidget(m_ToolbarButtons[SAVE]);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(m_ToolbarButtons[ATTACH]);


    // header frame
    const auto headerFormLayout = new QFormLayout(&m_HeaderFrame);
    headerFormLayout->addRow("Sender", &m_Data->SenderLineEdit);

    // recipients line edit with contact chooser
    auto const recipientRow = new QWidget(this);

    auto const recipientRowLayout = new QHBoxLayout(recipientRow);
    recipientRowLayout->setContentsMargins(0, 0, 0, 0);
    recipientRowLayout->setSpacing(5);

    recipientRowLayout->addWidget(&m_Data->RecipientsLideEdit);
    recipientRowLayout->addWidget(m_ContactChooser);

    headerFormLayout->addRow("Recipients", recipientRow);
    headerFormLayout->addRow("Subject", &m_Data->SubjectLineEdit);


    // body frame
    m_Data->TextBody.setPlaceholderText("Start typing...");


    const auto bodyLayout = new QVBoxLayout(&m_BodyFrame);
    bodyLayout->addWidget(&m_Data->TextBody);


    // set default email
    m_Data->SenderLineEdit.setReadOnly(true);
    m_Data->SenderLineEdit.setText("tra0163@vsb.cz");

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

void EmailEditor::ShowContactMenu()
{
    const auto users = m_DiContainer->GetService<UserRepo>()->GetAllUsers();

    auto* menu = new QMenu(m_ContactChooser);

    for (const auto& user : users)
    {
        QAction const* action = menu->addAction(user.Email);

        connect(action, &QAction::triggered, this, [this, user]() {
            QString currentText = m_Data->RecipientsLideEdit.text();

            if (!currentText.isEmpty())
            {
                currentText += ", ";
            }

            currentText += user.Email;

            m_Data->RecipientsLideEdit.setText(currentText);

            // Emit an event or handle the selection
            qDebug() << "Selected contact:" << user.Email;
        });
    }

    // Show the menu below the button
    menu->exec(QCursor::pos());
}

void EmailEditor::BindEvents()
{
    auto bus = this->m_DiContainer->GetService<EventBus>();

    connect(m_ToolbarButtons[SEND], &QPushButton::clicked, this, [this, bus] {
        auto recipients = m_Data->RecipientsLideEdit.text().split(',', Qt::SkipEmptyParts);

        for (const auto& recipient : recipients) {
            if (!IsValidEmail(recipient.trimmed())) {
                m_Data->RecipientsLideEdit.setStyleSheet("border: 2px solid red;");
                QMessageBox::warning(this, "Invalid Email", "One or more recipient email addresses are invalid.");
                return;
            } 
            else 
            {
                m_Data->RecipientsLideEdit.setStyleSheet("");
            }
        }

        bus->ForwardEmit<SendEmailClickedEvent>(*this->m_Data.get());
    });

    connect(m_ToolbarButtons[SAVE], &QPushButton::clicked, this, [this, bus] {
        bus->ForwardEmit<SaveEmailClickedEvent>(*this->m_Data.get());
    });

    connect(m_ToolbarButtons[ATTACH], &QPushButton::clicked, this, [this, bus] {
        const auto dialog = new QFileDialog(this);
        const auto files = dialog->getOpenFileNames(this, "Choose attachments");
        bus->ForwardEmit<AttachToEmailEvent>(files);
    });

    connect(m_ContactChooser, &QPushButton::clicked, this, &EmailEditor::ShowContactMenu);
}

