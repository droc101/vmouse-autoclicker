cmake_minimum_required(VERSION 3.19)
project(vmouse-autoclicker LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(KF6GlobalAccel REQUIRED)
find_package(KF6WidgetsAddons REQUIRED)

qt_standard_project_setup()

qt_add_executable(vmouse-autoclicker
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    vmouse.h vmouse.cpp
    COPYING
    README.md

)

target_link_libraries(vmouse-autoclicker
    PRIVATE
        Qt::Core
        Qt::Widgets
        KF6::GlobalAccel
        KF6::WidgetsAddons
)

include(GNUInstallDirs)

install(TARGETS vmouse-autoclicker
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET vmouse-autoclicker
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
