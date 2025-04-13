//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/ComposeView/AttachmentSideBar.h"

#include <QHeaderView>

AttachmentSideBar::AttachmentSideBar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("AttachmentSideBar", parent), m_DiContainer(diContainer)
    , m_AttachmentsView(new QTableView(this))
    , m_Model(new QStandardItemModel(0, 2, m_AttachmentsView))
{
    // project model into view
    m_AttachmentsView->setModel(m_Model);

    // setup model
    m_Model->setHeaderData(0, Qt::Horizontal, QString("Filename"));
    m_Model->setHeaderData(1, Qt::Horizontal, QString("Size"));

    // setup view
    const auto view = static_cast<QTableView*>(m_AttachmentsView);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // test
    m_Model->appendRow(QList<QStandardItem*>()
        << new QStandardItem("/file/path.txt") << new QStandardItem("123 B"));


    // layout view
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(m_AttachmentsView);
}

AttachmentSideBar::~AttachmentSideBar()
{
}
