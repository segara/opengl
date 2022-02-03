#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, const char** argv)
{
    SPDLOG_INFO("start program");
    //glfw 라이브러리 초기화
    if(!glfwInit())
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw:{}",description);
        return -1;
    }
    //버전지정
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw 윈도우 생성, 실패하면 에러출력 후 종료
    //monitor setting : null, context share : null
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if(!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//만들어진 window의 context를 사용
    
    //glad를 활용한 opengl함수 로딩
    //glfwGetProcAddress:gl함수 주소를 얻어내는 함수
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version :{}", glVerion);

    //glfw 루프 실행, 윈도우 close시 종료
    SPDLOG_INFO("start main loop");
    while(!glfwWindowShouldClose(window))
    {
         //glfwSwapBuffers(window);
        glfwPollEvents(); 
        // keyboard event, mouse event, window size 변경등의 event 수집 
        // 1/60초 만큼 이벤트를 수집하고 처리
        // 
    }
  

    glfwTerminate();
    return 0;
}