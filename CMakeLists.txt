cmake_minimum_required(VERSION 3.0)

project(JsonEditor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

#set(TS_FILES JsonEditor_ru_RU.ts)


set(SOURCES
    main.cpp
    controlpanel.cpp
    ValueModels/valueobject.cpp
    ValueModels/valueslistmodel.cpp
    )

set(HEADERS
    controlpanel.h
    ValueModels/valuemaps.h
    ValueModels/valueobject.h
    ValueModels/valueslistmodel.h
    )

set(DISTFILES
    qrc/qml.qrc
    .gitignore
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${DISTFILES})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Quick)
