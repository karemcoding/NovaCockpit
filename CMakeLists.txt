cmake_minimum_required(VERSION 3.16)

project(NovaCockpit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Location Positioning SerialBus)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appNovaCockpit
    main.cpp
    vehicledata.h
    vehicledata.cpp
)

qt_add_qml_module(appNovaCockpit
    URI NovaCockpit
    QML_FILES
        Main.qml
        SOURCES vehicledata.h vehicledata.cpp
    DEPENDENCIES
        QtQuick
        QtQuick.Controls
        QtQuick.Shapes
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNovaCockpit PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNovaCockpit
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNovaCockpit
    PRIVATE
        Qt6::Quick
        Qt6::Location
        Qt6::Positioning
        Qt6::SerialBus
)

include(GNUInstallDirs)
install(TARGETS appNovaCockpit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
