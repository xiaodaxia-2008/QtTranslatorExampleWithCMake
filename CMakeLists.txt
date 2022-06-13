# Copyright © 2022 Zen Shawn. All rights reserved. Created at 22:23:46, June 01,
# 2022

cmake_minimum_required(VERSION 3.13)

option(BUILD_SHARED_LIBS "build shared libs" OFF)
set(CMAKE_BUILD_TYPE
    "RelWithDebInfo"
    CACHE STRING "build type, Release/Debug/MinSizeRel/RelWithDebInfo")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

project(
  Temp
  VERSION 0.0.0
  DESCRIPTION "Instroduction about Temp")
set(CMAKE_INSTALL_PREFIX
    "$ENV{HOME}/Programs/Temp"
    CACHE PATH "install prefix")
include(GNUInstallDirs)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "Found ccache")
  set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

find_package(Eigen3 REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets)
find_package(Qt5LinguistTools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(Resources)
target_sources(Resources PRIVATE Resources.qrc)

qt5_create_translation(QM_FILES MainWindow.ui MainWindow.cpp MainWindow.h
                       MainWindow_en.ts MainWindow_zh.ts)

add_executable(main main.cpp MainWindow.cpp ${QM_FILES})
target_link_libraries(main PRIVATE Eigen3::Eigen Qt5::Widgets Resources)
