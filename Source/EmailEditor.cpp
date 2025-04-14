//
// Created by phatt on 4/8/25.
//

#include "EmailEditor.h"

EmailEditor::EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailEditor", parent), m_DiContainer(diContainer)
    // init children
    , m_ToolbarFrame("ToolbarFrame", this)
    , m_HeaderFrame("HeaderFrame", this)
    , m_BodyFrame("BodyFrame", this)
    , m_Data(CreateScope<DataContext>(this))  // data context
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
    headerFormLayout->addRow("Recipients", &m_Data->RecipientsLideEdit);
    headerFormLayout->addRow("Subject", &m_Data->SubjectLideEdit);


    // body frame
    m_Data->TextBody.setPlaceholderText("Start typing...");

    const auto bodyLayout = new QVBoxLayout(&m_BodyFrame);
    bodyLayout->addWidget(&m_Data->TextBody);


    // events
    BindEvents();
}

EmailEditor::~EmailEditor()
{
}

void EmailEditor::BindEvents() 
{
    const auto bus = this->m_DiContainer->GetService<EventBus>();

    connect(m_ToolbarButtons[SEND], &QPushButton::clicked, this, [this, &bus] {
        bus->Emit<SendEmailClickedEvent>(SendEmailClickedEvent(*this->m_Data.get()));
    });

    connect(m_ToolbarButtons[SAVE], &QPushButton::clicked, this, [this, &bus] {
        bus->Emit<SaveEmailClickedEvent>(SaveEmailClickedEvent(*this->m_Data.get()));
    });

    connect(m_ToolbarButtons[ATTACH], &QPushButton::clicked, this, [this, &bus] {
        const auto dialog = new QFileDialog(this);
        const auto files = dialog->getOpenFileNames(this, "Choose attachments");

        bus->ForwardEmit<AttachToEmailEvent>(files);
    });
}
