#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Render() {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f); //프레임 버퍼 화면을 클리어시 쓸 색상
    glClear(GL_COLOR_BUFFER_BIT); //프레임버퍼 클리어(GL_COLOR_BUFFER_BIT:색상버퍼를 지움)
}

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height); //open gl이 그림을 그릴 화면의 위치및 크기 설정
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

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
    SPDLOG_INFO("OpenGL context version :{}", glVersion);
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    //glfw 루프 실행, 윈도우 close시 종료
    SPDLOG_INFO("start main loop");
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); 
        Render();
        glfwSwapBuffers(window);

        // glfwPollEvents
        // keyboard event, mouse event, window size 변경등의 event 수집 
        // window에 대한 처리만(렌더링x)
        //glfwPollEvents 내부는 windows인 경우 : while(peekmessage) 로 구현 -> DispatchMessage : WM_DESTROY 등의 메세지를 메세지 처리함수로 보냄
    }
  

    glfwTerminate();
    return 0;
}