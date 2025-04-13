cmake_minimum_required(VERSION 3.30)
project(QtEmailClient)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  Sql
  REQUIRED)


add_executable(QtEmailClient 
        Source/main.cpp
        Source/MainWindow.cpp
        Header/MainWindow.h
        Header/Event/EventBus.h
        Header/Core/StdLib.h
        Header/Core/DIContainer.h
        Header/Core/QtWidgets.h
        Header/Core/IService.h
        Source/Menubar.cpp
        Header/Menubar.h
        Source/SideBar.cpp
        Header/SideBar.h
        Source/ViewPanel.cpp
        Header/ViewPanel.h
        Source/StatusBar.cpp
        Header/StatusBar.h
        Source/EmailView.cpp
        Header/Views/EmailView.h
        Source/ComposeView.cpp
        Header/Views/ComposeView.h
        Source/ContactsView.cpp
        Header/Views/ContactsView.h
        Header/Core/Core.h
        Header/Event/Events.h
        Header/Views/ViewsEnum.h
        Source/EmailEditor.cpp
        Header/Views/ComposeView/EmailEditor.h
        Source/CategoryList.cpp
        Header/Views/EmailView/CategoryList.h
        Source/QComponent.cpp
        Header/QComponent.h
        Source/EmailList.cpp
        Header/Views/EmailView/EmailList.h
        Source/EmailPreview.cpp
        Header/Views/EmailView/EmailPreview.h
        Header/Views/EmailView/EmailListViews/InboxListView.cpp
        Header/Views/EmailView/EmailListViews/InboxListView.h
        Header/Views/EmailView/EmailListViews/EmailListView.cpp
        Header/Views/EmailView/EmailListViews/EmailListView.h
        Source/EmailListSearchBar.cpp
        Header/Views/EmailView/EmailListSearchBar.h
        Source/EmailListFilterFrame.cpp
        Header/Views/EmailView/EmailListFilterFrame.h
        Source/EmailListSortFrame.cpp
        Header/Views/EmailView/EmailListSortFrame.h
        Source/AttachmentSideBar.cpp
        Header/Views/ComposeView/AttachmentSideBar.h
        Header/Views/EmailView/EmailListViews/EmailListViews.h
        Header/Database/DbContext.cpp
        Header/Database/DbContext.h
        Header/Database/EmailRepo.cpp
        Header/Database/EmailRepo.h
        Header/Database/DataModels.h
        Header/Database/AttachmentRepo.cpp
        Header/Database/AttachmentRepo.h
        Header/Database/UserRepo.cpp
        Header/Database/UserRepo.h
        Header/Core/Utility.h)


target_link_libraries(QtEmailClient
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)


target_include_directories(QtEmailClient PUBLIC
        Header
        Header/Core
        Header/Event
        Header/Views
        Header/Views/ComposeView
        Source
)


# cmake --build . --target run
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:QtEmailClient>
    DEPENDS QtEmailClient 
)


#target_precompile_headers(QtEmailClient PUBLIC Header/Core/Core.h)
