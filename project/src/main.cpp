#include <spdlog/spdlog.h>
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
    //glfw 루프 실행, 윈도우 close시 종료
    SPDLOG_INFO("start main loop");
    while(!glfwWindowShouldClose(window))
    {
         glfwSwapBuffers(window);
        //glfwPollEvents(); 
        // keyboard event, mouse event, window size 변경등의 event 수집 
        // 1/60초 만큼 이벤트를 수집하고 처리
        // 
    }

    glfwTerminate();
    return 0;
}