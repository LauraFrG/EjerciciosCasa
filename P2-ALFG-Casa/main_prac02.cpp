/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*--- Computación Gráfica e Interacción Humano-Computadora ---*/
/* ----------------   Versión VS-17 --------------------------*/
/*-------------  Fragoso Gasca Ana Laura  -----------------*/

#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint shaderProgramRed, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec4 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderRed = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.0f, 0.0f, 0.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	

	float vertices[] = 
	{
		// Positions //
		// --- C -- //
		-0.3f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.2f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.3f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.3f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.6f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.3f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.6f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.6f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.7f, 0.0f, 1.0f, 1.0f, 0.0f,
		
		-0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.6f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.6f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.6f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.3f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f,
		 
		-0.3f, 0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.2f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f,

		// --- G -- //
		0.8f, 0.8f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.7f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.7f, 0.7f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.7f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.4f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.3f, 0.7f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.7f, 0.7f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.3f, 0.7f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.7f, 0.0f, 1.0f, 1.0f, 1.0f,
		
		0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.4f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		
		0.4f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.8f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.9f, 0.2f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.9f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.9f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.9f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.7f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.8f, 0.3f, 0.0f, 1.0f, 1.0f, 1.0f,

		0.9f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.8f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.6f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.6f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
		
		// --- L -- Laura //
		-0.8f, -0.2f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.8f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.6f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.6f, -0.2f, 0.0f, 0.0f, 1.0f, 1.0f,

		-0.8f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.8f, -0.9f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.3f, -0.9f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.3f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f,
		
		// --- F -- Fragoso //
		0.8f, -0.3f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.7f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.7f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f,
		
		0.7f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.3f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.7f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f,

		0.3f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.3f, -0.9f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.9f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f,

		0.5f, -0.7f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.6f, -0.7f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.6f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,

		0.7f, -0.6f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.6f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.6f, -0.7f, 0.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] =
	{
		0, 1, 4, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, // -- C
		22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 
		36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, //-- G
		49, 50, 51, 52, 53, 54, 55, 56, // -- L
		57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 // -- F
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRed, 1, &myFragmentShaderRed, NULL);
	glCompileShader(fragmentShaderRed);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometría con Color
	shaderProgramRed = glCreateProgram();
	glAttachShader(shaderProgramRed, vertexShader);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderRed);
	glDeleteShader(fragmentShaderColor);

}

void display(void)
{
	glUseProgram(shaderProgramColor);

	glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glPointSize(5.0);
	// -- C --
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_POLYGON, 3, 4);
	glDrawArrays(GL_POLYGON, 7, 4);
	glDrawArrays(GL_POLYGON, 11, 4);
	glDrawArrays(GL_POLYGON, 15, 4);
	glDrawArrays(GL_TRIANGLES, 19, 3);

	// -- G
	glDrawArrays(GL_TRIANGLES, 22, 3);
	glDrawArrays(GL_POLYGON, 25, 4);
	glDrawArrays(GL_POLYGON, 29, 4);
	glDrawArrays(GL_TRIANGLES, 33, 3);
	glDrawArrays(GL_POLYGON, 36, 5);
	glDrawArrays(GL_POLYGON, 41, 4);
	glDrawArrays(GL_POLYGON, 45, 4);
	
	// -- L
	glDrawArrays(GL_POLYGON, 49, 4);
	glDrawArrays(GL_POLYGON, 53, 4);

	// -- F
	glDrawArrays(GL_TRIANGLES, 57, 3);
	glDrawArrays(GL_POLYGON, 60, 4);
	glDrawArrays(GL_POLYGON, 64, 4);
	glDrawArrays(GL_POLYGON, 68, 4);
	glDrawArrays(GL_TRIANGLES, 72, 3);
	
	glBindVertexArray(0);

	glUseProgram(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 2", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	//Configurar Shaders
	setupShaders();
    

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}