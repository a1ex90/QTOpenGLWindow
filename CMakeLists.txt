cmake_minimum_required(VERSION 3.10)
project(QTOpenGLWindow)

set(CMAKE_CXX_STANDARD 14)

# Enable QT Meta Object Compiler
set(CMAKE_AUTOMOC ON)
# Enable QT User Interface Compiler
set(CMAKE_AUTOUIC ON)
# Enable QT Rource Compiler
set(CMAKE_AUTORCC ON)

# Require QT5
find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

if (DEFINED BUILD_TESTS)
add_subdirectory(test)
endif()

# Find all Header and Source files
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS src/*.h qrc/*.qrc)
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES src/*.cpp)

add_library(${PROJECT_NAME}
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Quick
        Qt5::Widgets)