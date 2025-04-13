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
    const auto sendButton = new QPushButton("Send", &m_ToolbarFrame);
    const auto saveButton = new QPushButton("Save", &m_ToolbarFrame);
    const auto attachButton = new QPushButton("Attach", &m_ToolbarFrame);

    const auto toolbarLayout = new QHBoxLayout(&m_ToolbarFrame);
    toolbarLayout->addWidget(sendButton);
    toolbarLayout->addWidget(saveButton);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(attachButton);


    // header frame
    const auto headerFormLayout = new QFormLayout(&m_HeaderFrame);
    headerFormLayout->addRow("Sender", &m_Data->SenderLideEdit);
    headerFormLayout->addRow("Recipients", &m_Data->RecipientsLideEdit);
    headerFormLayout->addRow("Subject", &m_Data->SubjectLideEdit);


    // body frame
    m_Data->TextBody.setPlaceholderText("Start typing...");

    const auto bodyLayout = new QVBoxLayout(&m_BodyFrame);
    bodyLayout->addWidget(&m_Data->TextBody);


    // events
    connect(sendButton, &QPushButton::clicked, this, [this] {
        const auto bus = this->m_DiContainer->GetService<EventBus>();
        bus->Emit<EmailWrittenEvent>(EmailWrittenEvent(this->m_Data.get()));
    });
}

EmailEditor::~EmailEditor()
{
}
