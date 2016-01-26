#ifndef OPENGLMGR_HPP
#define OPENGLMGR_HPP

#include <vector>
#include <inttypes.h>
#include <GL/gl3w.h>

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include <GLFW/glfw3.h>
#include <vmath.h>
#include <ComponentMgr.hpp>

class OpenGLMgr: public ComponentMgr
{

    private:

	size_t _pov;
	GLuint program;
	GLuint line_program;
	GLFWwindow* _window;
	GLuint vao[2];
    GLuint buffer[2];
	GLint  mv_location;
    GLint  proj_location;
	GLint  line_mv_location;
    GLint  line_proj_location;

    float           aspect;
    vmath::mat4    proj_matrix;

	uint64_t time_spent;

    void setWindowTitle(const char * title)
    {
        glfwSetWindowTitle(_window, title);
    }

    static void glfw_onResize(GLFWwindow* window, int w, int h);

    static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);

    static void glfw_onMouseMove(GLFWwindow* window, double x, double y);

    static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
	
    public:

    OpenGLMgr(int windowWidth = 800, int windowHeight = 600, size_t pov = 0);
	~OpenGLMgr();
    virtual void update(uint16_t elapsed_time, std::vector<Entity>& entities);
	
};

#endif //OPENGLMGR_HPP
