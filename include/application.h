#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define FONT_PATH "dependencies/nanovg/example/Roboto-Bold.ttf"

namespace STAPP {

	class Application
	{
    public:
        Application();
        ~Application();
        int RunLoop(int argc, char *argv[]);

    protected:
        bool Initialize(int argc, char *argv[]);
        void Finalize();
        static void error_callback(int err, const char *msg);

    private:
        GLFWwindow *mWindow;
        NVGcontext *mVg;
        int mFont;  
    };

}