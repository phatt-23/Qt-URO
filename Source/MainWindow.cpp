//
// Created by phatt on 4/7/25.
//

#include "MainWindow.h"

#include "Menubar.h"
#include "../Header/Core/QtWidgets.h"
#include "SideBar.h"
#include "StatusBar.h"
#include "ViewPanel.h"

MainWindow::MainWindow(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QMainWindow(parent)
    , m_DiContainer(diContainer)
{
    setWindowTitle("Email Client");  // title

    const auto centralWidget = new QWidget(this);  // main widget
    const auto layout = new QHBoxLayout(centralWidget);  // layout
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    centralWidget->setLayout(layout);  // main widget use layout
    setCentralWidget(centralWidget);  // main widget is centered


    // initialize children
    m_Menubar = CreateRef<Menubar>(diContainer, centralWidget);
    m_SideBar = CreateRef<SideBar>(diContainer, centralWidget);
    m_ViewPanel = CreateRef<ViewPanel>(diContainer, centralWidget);
    m_StatusBar = CreateRef<StatusBar>(diContainer, centralWidget);

    setMenuBar(m_Menubar.get());
    setStatusBar(m_StatusBar.get());


    // layout children
    layout->addWidget(m_SideBar.get());
    layout->addWidget(m_ViewPanel.get());
    layout->setStretch(1, 1);   // ViewPanel

    BindEvents();
}

MainWindow::~MainWindow()
{
}

void MainWindow::BindEvents()
{
    auto const& bus = m_DiContainer->GetService<EventBus>();

    bus->Subscribe<QuitEvent>([this](QuitEvent const& e)
    { 
        QCoreApplication::quit();
    });

    bus->Subscribe<SideBarButtonClickedEvent>([this](SideBarButtonClickedEvent const& e)
    {
        if (e.View == ViewsEnum::QUIT) 
        {
            QCoreApplication::quit();
        }
    });
}
