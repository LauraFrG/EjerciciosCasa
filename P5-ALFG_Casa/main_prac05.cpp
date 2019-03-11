/*---------------------------------------------------------*/
/* ----------------   Práctica 5 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora ---------------*/
/*------------- Fragoso Gasca Ana Laura ---------------*/
/*------------- Versión Visual Studio 2017 ---------------*/

/*---------------------Instrucciones --------------------------

--------------- Brazo 1 (Derecha)
Hombro - T
Codo - Y
Muñeca - U
Pulgar - I
Índice - O
Medio - P
Anular - L
Meñique - K

--------------- Brazo 2 (Izquierda)
Hombro - G
Codo - H
Muñeca - J
Pulgar - C
Índice - V
Medio - B
Anular - N
Meñique - M

*/


#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;

//brazo
float angHom = 0.0f,
	angCo = 0.0f,
	angMu = 0.0f,
	angPu = 0.0f,
	angIn = 0.0f,
	angMe = 0.0f,
	angAn = 0.0f,
	angCh = 0.0f,
	angHomB = 0.0f,
	angCoB = 0.0f,
	angMuB = 0.0f,
	angPuB = 0.0f,
	angInB = 0.0f,
	angMeB = 0.0f,
	angAnB = 0.0f,
	angChB = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp para dedos
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection


	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

// -------------------------- Brazo 1 
	//Hombro-Amarillo
	model = glm::translate(model, glm::vec3(2.5, -2.25, 0));
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	glDrawArrays(GL_QUADS, 0, 24);

	//Bicep-Azul
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp; //¡IMPORTANTE!

	//Antebrazo
	model = glm::translate(model, glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(angCo), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Palma
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(angMu), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.5));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;
	modelTemp2 = model; //Cuando acabe cada dedo model = modelTemp2;

	//Pulgar - Falange 1
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Pulgar - Falange 2
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;

	//Indice - Falange 1
	model = glm::translate(model, glm::vec3(0.5, 0.375, 0));
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.1f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Indice - Falange 2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Indice - Falange 3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angIn*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.7f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;


	//Medio - Falange 1
	model = glm::translate(model, glm::vec3(0.5, 0.125, 0));
	model = glm::rotate(model, glm::radians(angMe), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.1f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Medio - Falange 2
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMe*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Medio - Falange 3
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMe*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.7f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;


	//Anular - Falange 1
	model = glm::translate(model, glm::vec3(0.5, -0.125, 0));
	model = glm::rotate(model, glm::radians(angAn), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Anular - Falange 2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAn*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Anular - Falange 3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAn*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.3f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;

	//Meñique - Falange 1
	model = glm::translate(model, glm::vec3(0.5, -0.375, 0));
	model = glm::rotate(model, glm::radians(angCh), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.7f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Meñique - Falange 2
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angCh*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Meñique - Falange 3
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angCh*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	// -------------------------- Brazo 2 
	model = modelTemp2;

	//Hombro-Amarillo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.5, -2.25, 0));
	model = glm::rotate(model, glm::radians(angHomB), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	glDrawArrays(GL_QUADS, 0, 24);


	//Bicep-Azul
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp; //¡IMPORTANTE!

	//Antebrazo
	model = glm::translate(model, glm::vec3(-1, 0, 0));
	model = glm::rotate(model, glm::radians(angCoB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(-3, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Palma
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	model = glm::rotate(model, glm::radians(angMuB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(-1, 1, 0.5));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;
	modelTemp2 = model; //Cuando acabe cada dedo model = modelTemp2;

	//Pulgar - Falange 1
	model = glm::translate(model, glm::vec3(0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPuB), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Pulgar - Falange 2
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPuB*0.7f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;

	//Indice - Falange 1
	model = glm::translate(model, glm::vec3(-0.5, 0.375, 0));
	model = glm::rotate(model, glm::radians(angInB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.1f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Indice - Falange 2
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angInB*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Indice - Falange 3
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angInB*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 0.7f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;


	//Medio - Falange 1
	model = glm::translate(model, glm::vec3(-0.5, 0.125, 0));
	model = glm::rotate(model, glm::radians(angMeB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.1f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Medio - Falange 2
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMeB*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Medio - Falange 3
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMeB*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.7f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;


	//Anular - Falange 1
	model = glm::translate(model, glm::vec3(-0.5, -0.125, 0));
	model = glm::rotate(model, glm::radians(angAnB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.7f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Anular - Falange 2
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAnB*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Anular - Falange 3
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAnB*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.3f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp2;

	//Meñique - Falange 1
	model = glm::translate(model, glm::vec3(-0.5, -0.375, 0));
	model = glm::rotate(model, glm::radians(angChB), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.7f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Meñique - Falange 2
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angChB*0.7f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	model = modelTemp;

	//Meñique - Falange 3
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angChB*0.9f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.2));
	projectionShader.setVec3("aColor", glm::vec3(0.3f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	// Cara
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, 0, 0));
	model = glm::scale(model, glm::vec3(1.5, 2.5, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Cuello
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -1.5, 0));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Cuerpo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -4.25, 0));
	model = glm::scale(model, glm::vec3(4, 5, 1));
	projectionShader.setVec3("aColor", glm::vec3(0.2f, 0.2f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Cintura
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -7.75, 0));
	model = glm::scale(model, glm::vec3(4, 2, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Pierna Der
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.5, -10.25, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Pierna Izq
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.5, -10.25, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Pie Der
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3, -12.25, 0));
	model = glm::scale(model, glm::vec3(4, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Pie Izq
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3, -12.25, 0));
	model = glm::scale(model, glm::vec3(4, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.5f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); 

	glBindVertexArray(0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.8f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.8f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.8f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.8f;

	//---------------------- BRAZO 1
	//Hombro
	if (glfwGetKey(window, GLFW_KEY_T)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if(angHom<90)
			angHom += 1.0f;
		}
		else {
			if(angHom>-90)
			angHom -= 1.0f;
		}
	}

	//Codo
	if (glfwGetKey(window, GLFW_KEY_Y)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angCo  < 0)
				angCo += 1.0f;
		}
		else {
			if (angCo > -140)
				angCo -= 1.0f;
		}
	}

	//Muñeca
	if (glfwGetKey(window, GLFW_KEY_U)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMu < 20)
				angMu += 1.0f;
		}
		else {
			if (angMu > -40)
				angMu -= 1.0f;
		}
	}

	//Pulgar
	if (glfwGetKey(window, GLFW_KEY_I)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angPu < 80)
				angPu += 1.0f;
		}
		else {
			if (angPu > 0)
				angPu -= 1.0f;
		}
	}

	//Indice
	if (glfwGetKey(window, GLFW_KEY_O)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angIn < 0)
				angIn += 1.0f;
		}
		else {
			if (angIn > -85)
				angIn -= 1.0f;
		}
	}


	//Medio
	if (glfwGetKey(window, GLFW_KEY_P)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMe < 0)
				angMe += 1.0f;
		}
		else {
			if (angMe > -85)
				angMe -= 1.0f;
		}
	}

	//Anular 
	if (glfwGetKey(window, GLFW_KEY_K)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angAn < 0)
				angAn += 1.0f;
		}
		else {
			if (angAn > -85)
				angAn -= 1.0f;
		}
	}


	//Meñique - Chiquito
	if (glfwGetKey(window, GLFW_KEY_L)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angCh < 0)
				angCh += 1.0f;
		}
		else {
			if (angCh > -85)
				angCh -= 1.0f;
		}
	}

	//------------------- BRAZO 2
	//Hombro
	if (glfwGetKey(window, GLFW_KEY_G)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angHomB < 90)
				angHomB += 1.0f;
		}
		else {
			if (angHomB > -90)
				angHomB -= 1.0f;
		}
	}

	//Codo
	if (glfwGetKey(window, GLFW_KEY_H)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angCoB < 0)
				angCoB -= 1.0f;
		}
		else {
			if (angCoB > -140)
				angCoB += 1.0f;
		}
	}

	//Muñeca
	if (glfwGetKey(window, GLFW_KEY_J)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMuB < 20)
				angMuB -= 1.0f;
		}
		else {
			if (angMuB > -40)
				angMuB += 1.0f;
		}
	}

	//Pulgar
	if (glfwGetKey(window, GLFW_KEY_C)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angPuB < 80)
				angPuB += 1.0f;
		}
		else {
			if (angPuB > 0)
				angPuB -= 1.0f;
		}
	}

	//Indice
	if (glfwGetKey(window, GLFW_KEY_V)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angInB < 0)
				angInB -= 1.0f;
		}
		else {
			if (angInB > -85)
				angInB += 1.0f;
		}
	}


	//Medio
	if (glfwGetKey(window, GLFW_KEY_B)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angMeB < 0)
				angMeB -= 1.0f;
		}
		else {
			if (angMeB > -85)
				angMeB += 1.0f;
		}
	}

	//Anular 
	if (glfwGetKey(window, GLFW_KEY_N)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angAnB < 0)
				angAnB -= 1.0f;
		}
		else {
			if (angAnB > -85)
				angAnB += 1.0f;
		}
	}


	//Meñique - Chiquito
	if (glfwGetKey(window, GLFW_KEY_M)) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) {
			if (angChB < 0)
				angChB -= 1.0f;
		}
		else {
			if (angChB > -85)
				angChB += 1.0f;
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}