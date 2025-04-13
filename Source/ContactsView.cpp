//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/ContactsView.h"

#include "Database/UserRepo.h"
#include <QHeaderView>
#include "Utility.h"

ContactsView::ContactsView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("ContactsView", parent), m_DiContainer(diContainer)
    , m_ContactsView(new QTableView(this))
    , m_ContactsModel(new QStandardItemModel(0, 3, m_ContactsView))
{
    // project model into view
    m_ContactsView->setModel(m_ContactsModel);

    // setup model
    m_ContactsModel->setHeaderData(0, Qt::Horizontal, "Email");
    m_ContactsModel->setHeaderData(1, Qt::Horizontal, "First Name");
    m_ContactsModel->setHeaderData(2, Qt::Horizontal, "Last Name");

    // fill up with users
    const auto userRepo = m_DiContainer->GetService<UserRepo>();
    const auto users = userRepo->GetAllUsers();

    for (const auto& user : users)
    {
        const auto row = CreateRow({ user.Email, user.FirstName, user.LastName });
        m_ContactsModel->appendRow(row);
    }

    // setup view
    const auto view = static_cast<QTableView*>(m_ContactsView);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(m_ContactsView);
}

ContactsView::~ContactsView()
{
}
