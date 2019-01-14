cmake_minimum_required(VERSION 3.12)
project(Login_w_struct C)

set(CMAKE_C_STANDARD 99)

set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT COM3)


add_executable(Login_w_struct main.c admin_setup.h admin_setup.c admin_menu.c admin_menu.h)