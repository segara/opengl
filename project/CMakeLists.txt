cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME project)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "hello, opengl!")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME}) #project setting 시작
add_executable(${PROJECT_NAME} src/main.cpp) #실행파일을 만든다

# include : cmake 의 추가적인 기능 사용할때
include(Dependency.cmake) #우리가 만든 dependency.cmake 파일

#프로젝트에 include / lib 옵션 추가 
# 위의 spdlog 관련 include / library 포함됨 (DEP_INCLUDE_DIR,DEP_LIB_DIR,DEP_LIBS)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# target_compile_definitions : define 매크로를 작성해주는 역할
target_compile_definitions(${PROJECT_NAME} PUBLIC 
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# dependency들이 먼저 빌드 될 수 있게 관계(의존성)설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST}) # dep_list가 먼저 빌드된후 project_name 이 빌드된다.