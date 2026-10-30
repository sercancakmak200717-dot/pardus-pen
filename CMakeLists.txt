cmake_minimum_required(VERSION 3.16)
project(pardus-pen LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg)

# Compile misc.c with C++ compiler to avoid MSVC C89 limitations
set_source_files_properties(src/utils/misc.c PROPERTIES LANGUAGE CXX)

set(SOURCES
    src/main.cpp
    src/SetupWidgets.cpp
    src/widgets/DrawingWidget.cpp
    src/widgets/WhiteBoard.cpp
    src/widgets/FloatingWidget.cpp
    src/widgets/FloatingSettings.cpp
    src/widgets/Background.cpp
    src/widgets/OverView.cpp
    src/widgets/ScreenshotWidget.cpp
    src/widgets/Button.cpp
    src/tools/update.cpp
    src/tools/icon.cpp
    src/tools/background.cpp
    src/tools/mainWindow.cpp
    src/tools/screenshot.cpp
    src/tools/save-load.cpp
    src/tools/pen.cpp
    src/utils/misc.c
    src/utils/eta-keyboard.cpp
    src/utils/Selection.cpp
    src/utils/Geometry.cpp
    src/utils/Settings.cpp
    src/utils/Storage.cpp
    src/utils/StrokeRecognition.cpp
    src/utils/ScreenShot.cpp
    data/resources.qrc
)

add_executable(pardus-pen ${SOURCES})

target_include_directories(pardus-pen PRIVATE
    include
    src
)

target_compile_definitions(pardus-pen PRIVATE
    screenshot
    QT6
    _USE_MATH_DEFINES
    _CRT_SECURE_NO_WARNINGS
    _CRT_NONSTDC_NO_DEPRECATE
    NOMINMAX
)

if(MSVC)
    target_compile_options(pardus-pen PRIVATE /EHsc /utf-8)
endif()

target_link_libraries(pardus-pen PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
)

if(WIN32)
    set_target_properties(pardus-pen PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
