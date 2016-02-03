#include <components/graphics/OpenGLMgr.hpp>
#include <ComponentReader.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static struct glParams
{

	int windowWidth;
	int windowHeight;

	double camPosX, camPosY, camPosZ;
	float camRotX, camRotY, camRotZ;
	
} glParams;

OpenGLMgr::OpenGLMgr(int windowWidth, int windowHeight)
{

    glParams.windowWidth = windowWidth;
    glParams.windowHeight = windowHeight;

	glParams.camPosX = 0;
	glParams.camPosY = 0;
	glParams.camPosZ = 10;

	glParams.camRotX = 0;
	glParams.camRotY = 0;
	glParams.camRotZ = 0;
	
	if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, GL_FALSE);
	glfwWindowHint(GLFW_STEREO, GL_FALSE);

	_window = glfwCreateWindow(glParams.windowWidth, glParams.windowHeight, "test", NULL, NULL);
    if (!_window)
    {
        fprintf(stderr, "Failed to open window\n");
        return;
    }

	glfwMakeContextCurrent(_window);

	glfwSetWindowSizeCallback(_window, glfw_onResize);
    glfwSetKeyCallback(_window, glfw_onKey);
    glfwSetMouseButtonCallback(_window, glfw_onMouseButton);
    glfwSetCursorPosCallback(_window, glfw_onMouseMove);
    glfwSetScrollCallback(_window, glfw_onMouseWheel);
	
	gl3wInit();

	GLuint line_vertex_shader;
	GLuint vertex_shader;
	GLuint line_fragment_shader;
	GLuint fragment_shader;

	//Source code for vertex shader
	static const GLchar *vertex_shader_source[]=
	{
            "#version 410 core                                                  \n"
            "                                                                   \n"
            "in vec3 position;                                                  \n"
            "                                                                   \n"
            "out VS_OUT                                                         \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} vs_out;                                                          \n"
            "                                                                   \n"
            "uniform mat4 mv_matrix;                                            \n"
            "uniform mat4 proj_matrix;                                          \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
			"                                                                   \n"
			"    vec3 position2;                                                 \n"
			"    position2[0] = position[0]*(0.25-position[2])/0.5;              \n"
			"    position2[1] = position[1]*(0.25-position[2])/0.5;              \n"
			"    position2[2] = position[2];              \n"
            "    gl_Position =  proj_matrix * mv_matrix * vec4(position2, 1.0);  \n"
            "    vs_out.color = vec4(position,1.0) * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);     \n"
            "}                                                                  \n"
	};

	//Source code for vertex shader
	static const GLchar *line_vertex_shader_source[]=
	{
            "#version 410 core                                                  \n"
            "                                                                   \n"
            "in vec3 position;                                                  \n"
            "                                                                   \n"
            "out VS_OUT                                                         \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} vs_out;                                                          \n"
            "                                                                   \n"
            "uniform mat4 mv_matrix;                                            \n"
            "uniform mat4 proj_matrix;                                          \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
			"                                                                   \n"
            "    gl_Position =  proj_matrix * mv_matrix * vec4(position, 1.0);  \n"
            "    vs_out.color = vec4(0.0, 0.0, 1.0, 1.0);     \n"
            "}                                                                  \n"
	};

	//Source code for fragment shader
	static const GLchar* fragment_shader_source[]=
	{
            "#version 410 core                                                  \n"
            "                                                                   \n"
            "out vec4 color;                                                    \n"
            "                                                                   \n"
            "in VS_OUT                                                          \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} fs_in;                                                           \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    color = fs_in.color;                                           \n"
            "}                                                                  \n"
	};

	// Create and compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	// Create and compile line vertex shader
	line_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(line_vertex_shader, 1, line_vertex_shader_source, NULL);
	glCompileShader(line_vertex_shader);

	// Create and compile fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	// Create and compile line fragment shader
	line_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(line_fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(line_fragment_shader);

	// Create program, attach shaders to it, and link it
	program =  glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	line_program =  glCreateProgram();
	glAttachShader(line_program, line_vertex_shader);
	glAttachShader(line_program, line_fragment_shader);

	glLinkProgram(program);
	glLinkProgram(line_program);

	// Delete the shaders as the program has them now
	glDeleteShader(line_vertex_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(line_fragment_shader);
	glDeleteShader(fragment_shader);

	mv_location = glGetUniformLocation(program, "mv_matrix");
    proj_location = glGetUniformLocation(program, "proj_matrix");
	
	line_mv_location = glGetUniformLocation(line_program, "mv_matrix");
    line_proj_location = glGetUniformLocation(line_program, "proj_matrix");
	
	glGenVertexArrays(2, vao);
	glGenBuffers(2, buffer);
	time_spent = 0;
	
    glBindVertexArray(vao[0]);
	
    static const GLfloat vertex_positions[] =
    {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_positions),
                 vertex_positions,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	
	glBindVertexArray(vao[1]);
	
	static const GLfloat line_vertex_positions[] =
    {
            -0.25f,  0.00f,  0.00f,
             0.25f,  0.00f,  0.00f,

             0.00f, -0.25f,  0.00f,
             0.00f,  0.25f,  0.00f,

             0.00f,  0.00f, -0.25f,
             0.00f,  0.00f,  0.25f
    };
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(line_vertex_positions),
                 line_vertex_positions,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
}

OpenGLMgr::~OpenGLMgr()
{

	glDeleteVertexArrays(2, vao);
    glDeleteProgram(program);
	glDeleteProgram(line_program);
    glDeleteBuffers(2, buffer);

	glfwDestroyWindow(_window);
    glfwTerminate();
	
}

void OpenGLMgr::setUp()
{

	glParams.camRotX = _pov->_spatial._default._rotX;
	glParams.camRotY = _pov->_spatial._default._rotY;
	glParams.camRotZ = _pov->_spatial._default._rotZ;
	
    glParams.camPosX = _pov->_spatial._default._x;
	glParams.camPosY = _pov->_spatial._default._y;
	glParams.camPosZ = _pov->_spatial._default._z;

	/* /!\ Be careful when reversing the object rotation to adjust the point of view: calling the rotate function first rotates around X, then Y, then Z.
	       If one wants to reverse such transformation, one might first rotate Z backward, then Y backward, then X backward. */
	proj_matrix = vmath::perspective(50.0f, (float)glParams.windowWidth / (float)glParams.windowHeight, 0.1f, 1000.0f)
		          *
		          vmath::rotate<float>(-glParams.camRotX+180, 0, 0)
		          *
		          vmath::rotate<float>(0, -glParams.camRotY, 0)
		          *
		          vmath::rotate<float>(0, 0, -glParams.camRotZ);
			      
	
	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    static const GLfloat one = 1.0f;
	
    glViewport(0, 0, glParams.windowWidth, glParams.windowHeight);
    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfv(GL_DEPTH, 0, &one);
	
}

void OpenGLMgr::update(const uint32_t elapsed_time_ns, GraphicsComponent& cmp, size_t id)
{

    glBindVertexArray(vao[0]);
	glEnableVertexAttribArray(0);
	
    glUseProgram(program);

	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
	
	const SpatialComponent spatial = _cmpRdr->getSpatialComponent(id);
	const ControlComponent ai = _cmpRdr->getControlComponent(id);
	
	// Note that use sliding origin.
	vmath::mat4 mv_matrix = vmath::translate<float>(spatial._default._x-glParams.camPosX,
												    spatial._default._y-glParams.camPosY,
												    spatial._default._z-glParams.camPosZ)
			                *
			                vmath::rotate<float>(spatial._default._rotX,
											     spatial._default._rotY,
											     spatial._default._rotZ);
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(vao[1]);
	glEnableVertexAttribArray(0);
	
	glUseProgram(line_program);

	glUniformMatrix4fv(line_proj_location, 1, GL_FALSE, proj_matrix);

	// Note that use sliding origin.
    mv_matrix = vmath::translate<float>(ai._default._targetX-glParams.camPosX,
												    ai._default._targetY-glParams.camPosY,
												    ai._default._targetZ-glParams.camPosZ);
		
	glUniformMatrix4fv(line_mv_location, 1, GL_FALSE, mv_matrix);
    glDrawArrays(GL_LINES, 0, 18);	
	
}

void OpenGLMgr::tearDown(){
	
	glfwSwapBuffers(_window);
    glfwPollEvents();

}

void OpenGLMgr::glfw_onResize(GLFWwindow* window, int w, int h)
{
    glParams.windowWidth = w;
	glParams.windowHeight = h;
}

void OpenGLMgr::glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
        
}

void OpenGLMgr::glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
        
}

void OpenGLMgr::glfw_onMouseMove(GLFWwindow* window, double x, double y)
{

}

void OpenGLMgr::glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{

}
