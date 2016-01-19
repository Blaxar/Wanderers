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

	GLuint program;
	GLFWwindow* window;
	GLuint vao;
    GLuint buffer;
	GLint           mv_location;
    GLint           proj_location;

    float           aspect;
    vmath::mat4    proj_matrix;

	uint64_t time_spent;
	
    public:

    OpenGLMgr();
	~OpenGLMgr();
    virtual void update(uint16_t elapsed_time, std::vector<Entity>& entities);
	
};

#endif //OPENGLMGR_HPP