cmake_minimum_required(VERSION 3.16)

project(SpaceInvaders_tutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSpaceInvaders_tutorial
    main.cpp
)

qt_add_qml_module(appSpaceInvaders_tutorial
    URI SpaceInvaders_tutorial
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES controller.h controller.cpp
        QML_FILES Bullet.qml
        SOURCES bullet.h bullet.cpp
        SOURCES bullet.h bullet.cpp
        SOURCES enemy.h enemy.cpp
        QML_FILES Enemy.qml
        QML_FILES GameOver.qml
        RESOURCES assets.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSpaceInvaders_tutorial PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSpaceInvaders_tutorial
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSpaceInvaders_tutorial
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appSpaceInvaders_tutorial
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_executable(controller_test controller.h controller.cpp
    bullet.h bullet.cpp
    bullet.h bullet.cpp
    enemy.h enemy.cpp
    controller_test.cpp)

target_link_libraries(controller_test
    PRIVATE Qt6::Quick
)
