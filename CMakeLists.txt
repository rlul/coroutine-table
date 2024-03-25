cmake_minimum_required(VERSION 3.10)

project(coroutine-table)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)

add_executable(coroutine-table WIN32 main.cpp "mainwindow.h" "mainwindow.cpp" "resource.h" "handlers.h" "handlers.cpp"   "person.h" "generators.h" "generators.cpp")
