#include "../Header/Views/ContactsView.h"

#include "Database/UserRepo.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

#include "ContactsView/ContactCard.h"

ContactsView::ContactsView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : BaseView("ContactsView", parent)
    , m_DiContainer(diContainer)
    , m_ScrollArea(new QScrollArea(this))
    , m_ContainerWidget(new QWidget(m_ScrollArea))
    , m_ContainerLayout(new QVBoxLayout(m_ContainerWidget))
    , m_AddNewContactButton(new QPushButton("Add New Contact", this))
{
    m_ScrollArea->setWidgetResizable(true);
    m_ScrollArea->setWidget(m_ContainerWidget);

    m_ContainerLayout->setAlignment(Qt::AlignTop);
    m_ContainerLayout->setContentsMargins(0, 0, 0, 0);
    m_ContainerLayout->setSpacing(0);

    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    auto* addNewContactLayout = new QHBoxLayout();
    addNewContactLayout->setContentsMargins(0, 0, 0, 0);
    addNewContactLayout->setSpacing(0);
    addNewContactLayout->addStretch();
    addNewContactLayout->addWidget(m_AddNewContactButton);

    layout->addWidget(m_ScrollArea); layout->setStretch(0, 1);
    layout->addLayout(addNewContactLayout); layout->setStretch(1, 0);

    m_ContainerWidget->setProperty("class", "container");
    m_ScrollArea->setObjectName("myScrollArea");
    
    BindEvents();
}

ContactsView::~ContactsView()
{
}

void ContactsView::OnEnter()
{
    BaseView::OnEnter();

    for (auto* ch : m_ContainerLayout->children())
    {
        if (auto* w = qobject_cast<QWidget*>(ch))
        {
            w->deleteLater();
        }
    }

    const auto userRepo = m_DiContainer->GetService<UserRepo>();
    const auto users = userRepo->GetAllUsers();

    for (const auto& user : users)
    {
        auto* contactCard = new ContactCard(user.Email, user.FirstName, user.LastName, this);
        m_ContainerLayout->addWidget(contactCard);
    }
}

void ContactsView::BindEvents()
{
    connect(m_AddNewContactButton, &QPushButton::clicked, [this]()
    {
        QDialog dialog(this);
        dialog.setWindowTitle("Add New Contact");
        dialog.setModal(true);

        auto* formLayout = new QFormLayout(&dialog);

        auto* firstNameEdit = new QLineEdit(&dialog);
        auto* lastNameEdit = new QLineEdit(&dialog);
        auto* emailEdit = new QLineEdit(&dialog);

        formLayout->addRow("First Name:", firstNameEdit);
        formLayout->addRow("Last Name:", lastNameEdit);
        formLayout->addRow("Email:", emailEdit);

        auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, &dialog);
        formLayout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted,
        [this, &dialog, firstNameEdit, lastNameEdit, emailEdit]()
        {
            const QString firstName = firstNameEdit->text().trimmed();
            const QString lastName = lastNameEdit->text().trimmed();
            const QString email = emailEdit->text().trimmed();

            if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty())
            {
                QMessageBox::warning(&dialog, "Invalid Input", "All fields are required.");
                return;
            }

            const auto userRepo = m_DiContainer->GetService<UserRepo>();

            User const newUser = {
                .Email = email, .FirstName = firstName, .LastName = lastName
            };

            if (!userRepo->AddUser(newUser))
            {
                QMessageBox::critical(&dialog, "Error", "Failed to add the contact.");
                return;
            }

            auto* contactCard = new ContactCard(email, firstName, lastName, this);
            m_ContainerLayout->addWidget(contactCard);

            dialog.accept();
        });

        connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        dialog.exec();
    });
}

