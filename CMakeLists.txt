cmake_minimum_required(VERSION 3.16)
project(MotoCluster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

# -----------------------------------------------------------------------
# Executable target.
# Stage 1 sources only: one Model class + one ViewModel class + main.cpp.
# More Model/ViewModel classes are added to this list in later stages.
# -----------------------------------------------------------------------
qt_add_executable(MotoCluster
    src/main.cpp
    src/models/vehicledata.h
    src/models/vehicledata.cpp
    src/viewmodels/clustervm.h
    src/viewmodels/clustervm.cpp
)

# -----------------------------------------------------------------------
# QML module: bundles our .qml files into the binary via the Qt Resource
# System (qrc), so no loose files need to ship alongside the executable.
# -----------------------------------------------------------------------
qt_add_qml_module(MotoCluster
    URI MotoCluster
    VERSION 1.0
    QML_FILES
        qml/main.qml
)

target_link_libraries(MotoCluster
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

# Ensures the app finds Qt's platform plugins etc. when run from the
# build directory during development.
include(GNUInstallDirs)
install(TARGETS MotoCluster
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
