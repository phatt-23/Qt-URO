//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/ComposeView/AttachmentSideBar.h"
#include "EmailEditor.h"
#include "EventBus.h"
#include "SideBar.h"

#include <QHeaderView>

AttachmentSideBar::AttachmentSideBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("AttachmentSideBar", parent), m_DiContainer(diContainer)
    , m_AttachmentsView(new QTableView(this))
    // , m_Model(new QStandardItemModel(0, 2, m_AttachmentsView))
    , m_Model(new QStandardItemModel(0, 1, m_AttachmentsView))
{
    // project model into view
    m_AttachmentsView->setModel(m_Model);

    // setup model
    m_Model->setHeaderData(0, Qt::Horizontal, QString("Filename"));
    // m_Model->setHeaderData(1, Qt::Horizontal, QString("Size"));

    // setup view
    const auto view = static_cast<QTableView*>(m_AttachmentsView);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // test

    // layout view
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(m_AttachmentsView);

    BindEvents();
}

AttachmentSideBar::~AttachmentSideBar()
{
}

// struct AttachToEmailEvent final : public EventBase {
//     AttachToEmailEvent(const QStringList& attachments) : EventBase(), Attachments(attachments) {}
//     const QList<QString>& Attachments;
// };

void AttachmentSideBar::BindEvents()
{
    auto bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<SideBarButtonClickedEvent>([](const SideBarButtonClickedEvent& e) {
        qInfo() << "HERE" << e;
    });

    bus->Subscribe<AttachToEmailEvent>([this](const AttachToEmailEvent& e) {
        qInfo() << "HEEREEE:" << e;

        for (const QString& a : e.Attachments) 
        {
            m_Model->appendRow(QList<QStandardItem*>() << new QStandardItem(a));
        }
    });


    auto view = (QTableView*)m_AttachmentsView;

    connect(view, &QAbstractItemView::pressed, this, [this, view](const QModelIndex& index) {
        qInfo() << "Show menu for index" << index;

        QMenu* menu = new QMenu(view); 
        QAction* removeAction = menu->addAction("Remove");

        connect(removeAction, &QAction::triggered, this, [this, index]() {
            qInfo() << "Remove action triggered for index" << index;

            m_Model->removeRow(index.row());
        });

        menu->exec(QCursor::pos());  // Show the menu at the cursor position
    });
}

QList<QString> AttachmentSideBar::GetAttachments() const
{
    QStringList files;
    for (int i = 0; m_Model->rowCount(); i++)
    {
        files.append(m_Model->item(i)->text());
    }
    return files;
}


