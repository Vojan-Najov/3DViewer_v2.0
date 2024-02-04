cmake_minimum_required(VERSION 3.5)

project(3DViewer-v2.0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

add_subdirectory(${CMAKE_SOURCE_DIR}/gifLib)

set(PROJECT_SOURCES
        main.cc
        view.cc
        view.h
        controller.cc
        controller.h
        oglwindow.cc
        oglwindow.h
        view.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer-v2.0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer-v2.0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer-v2.0 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer-v2.0
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(3DViewer-v2.0 PUBLIC ${CMAKE_SOURCE_DIR}/../libviewer)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

target_link_libraries(3DViewer-v2.0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                PRIVATE Qt6::OpenGLWidgets
                                PUBLIC ${CMAKE_SOURCE_DIR}/../libviewer/libviewer.a
                                PRIVATE QtGifImage::QtGifImage
                                PUBLIC ${OPENGL_LIBRARIES}
)

set_target_properties(3DViewer-v2.0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer-v2.0)
endif()
