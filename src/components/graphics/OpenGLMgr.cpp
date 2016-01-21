#include <components/graphics/OpenGLMgr.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

OpenGLMgr::OpenGLMgr()
{

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

	window = glfwCreateWindow(800, 600, "test", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open window\n");
        return;
    }

	glfwMakeContextCurrent(window);
	
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
	
	proj_matrix = vmath::perspective(50.0f, (float)800 / (float)600, 0.1f, 1000.0f)*
		          vmath::translate((float)0,(float)0,(float)-10);
	
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

	glfwDestroyWindow(window);
    glfwTerminate();
	
}

void OpenGLMgr::update(uint16_t elapsed_time, std::vector<Entity>& entities)
{

	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    static const GLfloat one = 1.0f;
	time_spent += elapsed_time;
	
    glViewport(0, 0, 800, 600);
    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfv(GL_DEPTH, 0, &one);

	glBindVertexArray(vao[0]);
	glEnableVertexAttribArray(0);
	
    glUseProgram(program);

	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

	for(Entity& ent : entities)
	{

		vmath::mat4 mv_matrix = vmath::translate((float)ent._spatial._default._x,
												 (float)ent._spatial._default._y,
												 (float)ent._spatial._default._z)
			                    *
			                    vmath::rotate((float)ent._spatial._default._rotX,
											  (float)ent._spatial._default._rotY,
											  (float)ent._spatial._default._rotZ);
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

	}


	glBindVertexArray(vao[1]);
	glEnableVertexAttribArray(0);
	
	glUseProgram(line_program);

	glUniformMatrix4fv(line_proj_location, 1, GL_FALSE, proj_matrix);

	for(Entity& ent : entities)
	{

		vmath::mat4 mv_matrix = vmath::translate((float)ent._ai._default._targetX,
												 (float)ent._ai._default._targetY,
												 (float)ent._ai._default._targetZ);
		glUniformMatrix4fv(line_mv_location, 1, GL_FALSE, mv_matrix);
        glDrawArrays(GL_LINES, 0, 18);

	}
	
	glfwSwapBuffers(window);
    glfwPollEvents();	
	
}
