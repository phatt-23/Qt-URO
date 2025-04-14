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


file(GLOB_RECURSE headers "Header/**.h")
file(GLOB_RECURSE sources "Source/**.cpp")


add_executable(QtEmailClient 
        ${headers}
        ${sources}
)


target_link_libraries(QtEmailClient
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)


target_include_directories(QtEmailClient PUBLIC
        ./Header
        ./Header/Core
        ./Header/Event
        ./Header/Views
        ./Header/Views/ComposeView
        ./Header/Views/EmailPreview
        ./Header/Views/EmailView/EmailListViews
        ./Header/Views/EmailView/EmailCardList
        ./Header/Database
        ./Source
)


# cmake --build . --target run
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:QtEmailClient>
    DEPENDS QtEmailClient 
)


#target_precompile_headers(QtEmailClient PUBLIC Header/Core/Core.h)
