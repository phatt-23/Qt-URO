#include "../Header/Views/ComposeView/AttachmentSideBar.h"

#include "AttachmentSidebarCard.h"
#include "AttachmentViewerDialog.h"
#include "EmailEditor.h"
#include "EventBus.h"



AttachmentSideBar::AttachmentSideBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("AttachmentSideBar", parent), m_DiContainer(diContainer)
    , m_ContainerWidget(new QWidget(this))
    , m_ContainerLayout(new QVBoxLayout(m_ContainerWidget))
{
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    m_ContainerLayout->setAlignment(Qt::AlignTop);
    m_ContainerLayout->setContentsMargins(0, 0, 0, 0);
    m_ContainerLayout->setSpacing(0);

    m_ContainerWidget->setLayout(m_ContainerLayout);
    scrollArea->setWidget(m_ContainerWidget);

    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(new QLabel("Attachments", this));

    auto* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    layout->addWidget(scrollArea);

    BindEvents();
}

AttachmentSideBar::~AttachmentSideBar()
{
}

void AttachmentSideBar::Clear() const
{
    while (const QLayoutItem* item = m_ContainerLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void AttachmentSideBar::BindEvents()
{
    auto const bus = m_DiContainer->GetService<EventBus>();

    // Subscribe to the AttachToEmailEvent
    bus->Subscribe<AttachToEmailEvent>([this](const AttachToEmailEvent& e) {
        if (m_Readonly)
            return;

        for (const QString& filepath : e.Attachments) {
            AddAttachment(filepath);
        }
    });
}

void AttachmentSideBar::AddAttachment(const QString& filepath)
{
    const auto card = new AttachmentSidebarCard(filepath, this);
    m_ContainerLayout->addWidget(card);

    connect(card, &AttachmentSidebarCard::RemoveClicked, [this](AttachmentSidebarCard* cardIntance)
    {
        cardIntance->deleteLater();
    });
}


QList<QString> AttachmentSideBar::GetAttachments() const
{
    QStringList files;
    for (int i = 0; i < m_ContainerLayout->count(); ++i) {
        auto const* widget = m_ContainerLayout->itemAt(i)->widget();
        if (auto const* label = widget->findChild<QLabel*>()) {
            files.append(label->text());
        }
    }
    return files;
}