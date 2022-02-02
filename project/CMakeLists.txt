cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME project)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME}) #project setting 시작
add_executable(${PROJECT_NAME} src/main.cpp) #실행파일을 만든다