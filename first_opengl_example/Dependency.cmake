# External Project관련 명령어 셋 추가
# include : cmake 의 추가적인 기능 사용할때 
# ExternalProject_Add를 사용하기 위해  ExternalProject 기능 추가
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# ExternalProject_Add : git clone받은후 cmake 까지 실행
#spdlog : fast logger library
ExternalProject_Add(
    dep_spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x" # branch / tag 지정
    GIT_SHALLOW 1 # 가장 최신의 내역만 다운
    UPDATE_COMMAND "" # git update 안씀
    PATCH_COMMAND "" # 사용자가 고치는 옵션 안씀
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} #cmake configure 시 사용 : -D(변수=값) , CMAKE_INSTALL_PREFIX:인스톨 경로
    TEST_COMMAND ""
)
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) # CONFIG:debug setting일때 d를 붙일것, DEP_LIBS는 위에 값이 정의되있지 않은데 그러면 빈값이 들어감

##### glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.2" # branch / tag 지정
    GIT_SHALLOW 1 # 가장 최신의 내역만 다운
    UPDATE_COMMAND "" # git update 안씀
    PATCH_COMMAND "" # 사용자가 고치는 옵션 안씀
    TEST_COMMAND ""
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} #cmake configure 시 사용 : -D(변수=값) , CMAKE_INSTALL_PREFIX:인스톨 경로
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
)
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3) 
##### glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    GIT_TAG "v0.1.34" # branch / tag 지정
    GIT_SHALLOW 1 # 가장 최신의 내역만 다운
    UPDATE_COMMAND "" # git update 안씀
    PATCH_COMMAND "" # 사용자가 고치는 옵션 안씀
    TEST_COMMAND ""
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} #cmake configure 시 사용 : -D(변수=값) , CMAKE_INSTALL_PREFIX:인스톨 경로
        -DGLAD_INSTALL=ON
    )
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad) 