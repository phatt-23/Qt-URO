//
// Created by phatt on 4/7/25.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "Core/StdLib.h"
#include "DIContainer.h"
#include "Menubar.h"
#include "SideBar.h"
#include "StatusBar.h"
#include "ViewPanel.h"


class MainWindow final : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ref<DIContainer> m_DiContainer;

    Ref<Menubar> m_Menubar;
    Ref<SideBar> m_SideBar;
    Ref<ViewPanel> m_ViewPanel;
    Ref<StatusBar> m_StatusBar;
};

#endif //MAINWINDOW_H
