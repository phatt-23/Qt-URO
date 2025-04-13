//
// Created by phatt on 4/8/25.
//

#include "../Header/Views/EmailView/CategoryList.h"

CategoryList::CategoryList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("CategoryList", parent), m_DiContainer(diContainer)
    // init children
    , m_CategoryView(CreateScope<QListView>(this))
{
    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(m_CategoryView.get());


    // represents model (data)
    const auto itemModel = new QStandardItemModel(0, 1, m_CategoryView.get());
    itemModel->setHeaderData(0, Qt::Horizontal, QString("Category"));


    QList<QString> categories = {
        "Inbox",
        "Drafts",
        "Sent Mail",
        "All Mail",
        "Spam",
        "Bin",
        "Important",
        "Starred",
    };

    for (const auto& category : categories) {
        itemModel->appendRow(new QStandardItem(category));
    }

    // projects model
    m_CategoryView->setModel(itemModel);
}
