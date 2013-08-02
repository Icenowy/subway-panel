project(heartlenv-panel)
cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)
find_package(X11 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(heartlenv-panel_SRCS panelapplication.cpp applet.cpp applets/window-list/instanceofwindow.cpp heartlenv-panel.cpp main.cpp applets/menu/main.cpp applets/window-list/main.cpp)
qt4_automoc(${heartlenv-panel_SRCS})
add_executable(heartlenv-panel ${heartlenv-panel_SRCS})
target_link_libraries(heartlenv-panel ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIB_DEPENDENCIES} heartlenv)
install(TARGETS heartlenv-panel RUNTIME DESTINATION bin)
