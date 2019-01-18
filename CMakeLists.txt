cmake_minimum_required(VERSION 3.12)
project(Login_w_struct C)

set(CMAKE_C_STANDARD 99)

add_executable(Login_w_struct main.c admin_setup.h admin_setup.c admin_menu.c admin_menu.h serial_communication.c serial_communication.h db_interaction.c db_interaction.h sqlite3.h sqlite3.c sqlite3ext.h user_menu.c user_menu.h)