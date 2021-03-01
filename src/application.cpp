#include "application.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

namespace STAPP {

    Application::Application(): mWindow(NULL), mVg(NULL) {}

    Application::~Application()
    {
        Finalize();
    }

    int Application::RunLoop(int argc, char *argv[])
    {
        if (!Initialize(argc, argv)) {
            return 1;
        }

        while (!glfwWindowShouldClose(mWindow)) {
            int w, h, w2, h2;
            glfwGetWindowSize(mWindow, &w, &h);
            glfwGetFramebufferSize(mWindow, &w2, &h2);
            float pixel_ratio = static_cast<float>(w2) / w;
            glViewport(0, 0, w2, h2);

            glClearColor(0.3, 0.3, 0.32, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            nvgBeginFrame(mVg, w, h, pixel_ratio);

            nvgFontSize(mVg, 96);
            nvgFontFace(mVg, "font");
            nvgFillColor(mVg, nvgRGBA(255, 255, 255, 255));
            nvgTextAlign(mVg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            char buf[256];
            snprintf(buf, sizeof buf, "%dx%d | %dx%d", w, h, w2, h2);
            nvgText(mVg, 10, 10, buf, NULL);
            nvgText(mVg, 10, 100, "Hello NanoVG By iMacwink !", NULL);

            nvgEndFrame(mVg);

            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }

        return 0;
    }

    bool Application::Initialize(int argc, char *argv[])
    {
        if (!glfwInit()) {
            printf("glfwInit() failed\n");
            return false;
        }

        glfwSetErrorCallback(error_callback);
        #ifndef _WIN32
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #endif

        mWindow = glfwCreateWindow(1920, 1080, "NanoVG Example By iMacwink", NULL, NULL);
        if (mWindow == NULL) {
            printf("glfwCreateWindow() failed\n");
            return false;
        }

        glfwMakeContextCurrent(mWindow);

        // Initialize GLAD.
        // Make sure that glad has been initialized successfully.
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return 0;
        }

        // Set the viewport
        glViewport(0, 0, 1024, 768);

        mVg = nvgCreateGL3(NVG_ANTIALIAS);
        if (mVg == NULL) {
            printf("nvgCreateGL3() failed\n");
            return false;
        }
        
        mFont = nvgCreateFont(mVg, "font", FONT_PATH);
        if (mFont < 0) {
            printf("nvgCreateFont() failed\n");
            return false;
        }

        glfwSwapInterval(0);

        return true;
    }

    void Application::Finalize()
    {
        if (mVg != NULL) {
            nvgDeleteGL3(mVg);
            mVg = NULL;
        }

        if (mWindow != NULL) {
            glfwDestroyWindow(mWindow);
            mWindow = NULL;
        }

        glfwTerminate();
    }

    void Application::error_callback(int err, const char *msg)
    {
        printf("GLFW error %d: %s\n", err, msg);
    }
}