cmake_minimum_required(VERSION 3.14)

project(QT_FTGL_CMAKE VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui OpenGL REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui OpenGL REQUIRED)

add_subdirectory(GLES1_Wrapper)
add_subdirectory(freetype-cmake)
add_subdirectory(glyphy)
include_directories(glyphy/src)

set(PROJECT_SOURCES
    main.cpp
    GLWindow.cpp
    ChronoTimer.cpp
    glyphy/demo/demo-atlas.cc
    glyphy/demo/demo-buffer.cc
    glyphy/demo/demo-font.cc
    glyphy/demo/demo-glstate.cc
    glyphy/demo/demo-shader.cc
    glyphy/demo/demo-view.cc
    glyphy/demo/matrix4x4.c
    glyphy/demo/trackball.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_FTGL_CMAKE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cmake_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT_FTGL_CMAKE SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT_FTGL_CMAKE
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    QT_FTGL_CMAKE PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    glyphy
    GLES1_Wrapper
)

set_target_properties(QT_FTGL_CMAKE PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT_FTGL_CMAKE)
endif()
