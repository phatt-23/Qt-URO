//
// Created by phatt on 4/7/25.
//

#include "../Header/Menubar.h"

#include "ComposeView.h"
#include "MainWindow.h"

Menubar::Menubar(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QMenuBar(parent)
    , m_DiContainer(diContainer)
{
    const auto fileMenu = this->addMenu("File");
    auto* newAction = fileMenu->addAction("New", QKeySequence(Qt::CTRL | Qt::Key_N));
    fileMenu->addAction("Open", QKeySequence(Qt::CTRL | Qt::Key_O));
    fileMenu->addSeparator();
    fileMenu->addAction("Save", QKeySequence(Qt::CTRL | Qt::Key_S));
    fileMenu->addAction("Save As", QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    fileMenu->addSeparator();
    auto* quitAction = fileMenu->addAction("Quit", QKeySequence(Qt::CTRL | Qt::Key_Q));

    const auto editMenu = this->addMenu("Edit");
    editMenu->addAction("Undo", QKeySequence(Qt::CTRL | Qt::Key_Z));
    editMenu->addAction("Redo", QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Z));
    editMenu->addSeparator();
    editMenu->addAction("Cut");
    editMenu->addAction("Copy");
    editMenu->addAction("Paste");
    editMenu->addSeparator();
    editMenu->addAction("Find");
    editMenu->addAction("Find All");
    editMenu->addSeparator();
    editMenu->addAction("Settings");

    const auto viewMenu = this->addMenu("View");
    auto *composeAction = viewMenu->addAction("Compose", QKeySequence(Qt::CTRL | Qt::Key_1));
    auto *mailAction = viewMenu->addAction("Mail", QKeySequence(Qt::CTRL | Qt::Key_2));
    auto *contactsAction = viewMenu->addAction("Contacts", QKeySequence(Qt::CTRL | Qt::Key_3));

    const auto helpMenu = this->addMenu("Help");
    helpMenu->addAction(":(");

    auto const& bus = m_DiContainer->GetService<EventBus>();

    connect(newAction, &QAction::triggered, [this, bus]
    {
        auto* dialog = new QDialog(this);
        dialog->setWindowTitle("New email");
        dialog->setModal(true);

        auto* dialogLayout = new QVBoxLayout();
        dialogLayout->setContentsMargins(0, 0, 0, 0);
        dialogLayout->setSpacing(0);

        dialog->setLayout(dialogLayout);

        dialogLayout->addWidget(new ComposeView(m_DiContainer, this, true));

        dialog->show();
    });

    connect(quitAction, &QAction::triggered, [this, bus]()
    {
        bus->ForwardEmit<QuitEvent>();
    });

    connect(composeAction, &QAction::triggered, [this, bus]()
    {
        // fake
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::COMPOSE_VIEW);
    });

    connect(mailAction, &QAction::triggered, [this, bus]()
    {
        // fake
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::EMAIL_VIEW);
    });

    connect(contactsAction, &QAction::triggered, [this, bus]()
    {
        // fake
        bus->ForwardEmit<SideBarButtonClickedEvent>(ViewsEnum::CONTACTS_VIEW);
    });
}
