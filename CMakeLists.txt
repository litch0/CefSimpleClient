cmake_minimum_required(VERSION 3.17)
project(cefClientTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(cefClientTest main.cpp SimpleApp.h SimpleHandler.h)
include_directories(Libs/)

target_link_libraries(cefClientTest cef_dll_wrapper cef -B/home/litch0/repo/MyRepos/cefClientTest/Libs/Release)