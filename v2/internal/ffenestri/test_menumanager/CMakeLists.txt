cmake_minimum_required(VERSION 3.17)
project(test_menumanager)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -g")

add_executable(test_menumanager test.c minunit.h)
add_library(menus STATIC ../menu_manager.c ../menu.c ../menu_tray.c ../menu_item.c)
add_library(common STATIC ../common.c ../utf8.h)
add_library(json STATIC ../json.c)
add_library(vec STATIC ../vec.c)

if( CMAKE_HOST_APPLE )
    add_library(platform STATIC ../menu_darwin.c)
    target_link_libraries(test_menumanager objc)
endif()

target_link_libraries(test_menumanager vec json common menus platform)
include_directories(..)
include_directories(.)