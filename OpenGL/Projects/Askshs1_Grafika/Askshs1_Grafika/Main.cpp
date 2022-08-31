// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>


// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <D:\Work\OpenGL\Projects\Askshs1_Grafika\Askshs1_Grafika\shader.hpp>
#include <D:\Work\OpenGL\Projects\Askshs1_Grafika\Askshs1_Grafika\control.hpp>
#include <D:\Work\OpenGL\glm\glm\gtc\matrix_transform.hpp>
#include <D:\Work\OpenGL\glm\glm\gtx\transform.hpp>
#include <D:\Work\OpenGL\glm\glm\gtc\type_ptr.hpp>
#include <D:\Work\OpenGL\Projects\Askshs1_Grafika\Askshs1_Grafika\objloader.hpp>
#include <D:\Work\OpenGL\Projects\Askshs1_Grafika\Askshs1_Grafika\stb_image.hpp>

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(600, 600, u8"Συγκρουόμενα", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version .\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 600 / 2, 600 / 2);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID  = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint programID1 = LoadShaders("ObjectsVertexShader.vertexshader", "ObjectsFragmentShader.fragmentshader");
	GLuint programID2 = LoadShaders("SphereVertexTexture.vertexshader", "SphereFragmentTexture.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID  = glGetUniformLocation(programID, "MVP");
	GLuint MatrixID1 = glGetUniformLocation(programID1, "MVP");
	GLuint mycolorID = glGetUniformLocation(programID1, "color");
	GLuint MatrixID2 = glGetUniformLocation(programID2, "MVP");
	GLuint TextureID = glGetUniformLocation(programID2, "ourTexture");
	
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Create Random numbers between 0 and 1 
	srand(time(0));
	GLfloat red, green, blue;
	red   =(GLfloat)rand() / RAND_MAX;
	green =(GLfloat)rand() / RAND_MAX;
	blue  =(GLfloat)rand() / RAND_MAX;

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data_bigcube[] = {
		0.0f,     0.0f,     0.0f,
		0.0f,     0.0f,     100.0f,
		0.0f,     100.0f,   100.0f,
		100.0f,   100.0f,   0.0f,
		0.0f,     0.0f,     0.0f,
		0.0f,     100.0f,   0.0f,
		100.0f,   0.0f,     100.0f,
		0.0f,     0.0f,     0.0f,
		100.0f,   0.0f,     0.0f,
		100.0f,   100.0f,   0.0f,
		100.0f,   0.0f,     0.0f,
		0.0f,     0.0f,     0.0f,
		0.0f,     0.0f,     0.0f,
		0.0f,     100.0f,   100.0f,
		0.0f,     100.0f,   0.0f,
		100.0f,   0.0f,     100.0f,
		0.0f,     0.0f,     100.0f,
		0.0f,     0.0f,     0.0f,
		0.0f,     100.0f,   100.0f,
		0.0f,     0.0f,     100.0f,
		100.0f,   0.0f,     100.0f,
		100.0f,   100.0f,   100.0f,
		100.0f,   0.0f,     0.0f,
		100.0f,   100.0f,   0.0f,
		100.0f,   0.0f,     0.0f,
		100.0f,   100.0f,   100.0f,
		100.0f,   0.0f,     100.0f,
		100.0f,   100.0f,   100.0f,
		100.0f,   100.0f,   0.0f,
		0.0f,     100.0f,   0.0f,
		100.0f,   100.0f,   100.0f,
		0.0f,     100.0f,   0.0f,
		0.0f,     100.0f,   100.0f,
		100.0f,   100.0f,   100.0f,
		0.0f,     100.0f,   100.0f,
		100.0f,   0.0f,     100.0f
	};

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data_bigcube[] = {
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
	};

	//Small cube
	static const GLfloat g_vertex_buffer_data_smallcube[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	///////LOAD BIG CUBE///////////////////////////////////////////
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_bigcube), g_vertex_buffer_data_bigcube, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_bigcube), g_color_buffer_data_bigcube, GL_STATIC_DRAW);

	///////LOAD SMALL CUBE//////////////////////////////////////////
	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_smallcube), g_vertex_buffer_data_smallcube, GL_STATIC_DRAW);

	//////////////////////LOAD SPHERE///////////////////////////////
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool sphere = loadOBJ("Sphere.obj", vertices, uvs, normals);

	GLuint Spherevertexbuffer;
	glGenBuffers(1, &Spherevertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Spherevertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint Sphereuvbuffer;
	glGenBuffers(1, &Sphereuvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Sphereuvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint Spherenormalbuffer;
	glGenBuffers(1, &Spherenormalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Spherenormalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec2), &normals[0], GL_STATIC_DRAW);

	/////////////////////////LOAD CYLINDER//////////////////////////
	std::vector<glm::vec3> vertices1;
	std::vector<glm::vec2> uvs1;
	std::vector<glm::vec3> normals1; // Won't be used at the moment.
	bool cylinder = loadOBJ("Cylinder.obj", vertices1, uvs1, normals1);

	GLuint Cylindervertexbuffer;
	glGenBuffers(1, &Cylindervertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Cylindervertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

	GLuint Cylinderuvbuffer;
	glGenBuffers(1, &Cylinderuvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinderuvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs1.size() * sizeof(glm::vec2), &uvs1[0], GL_STATIC_DRAW);
	
	GLuint Cylindernormalbuffer;
	glGenBuffers(1, &Cylindernormalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Cylindernormalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals1.size() * sizeof(glm::vec2), &normals1[0], GL_STATIC_DRAW);
	
	//////////SET UP TEXTURE FOR THE SPHERE/////////////////////////
	
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glUniform1i(glGetUniformLocation(programID2, "texture1"), 0);

	GLfloat xpos1 = 50.0f;
	GLfloat ypos1 = 50.0f;
	GLfloat zpos1 = 50.0f;
	int checker =1;
	/////////////////////////RENDERING//////////////////////////////
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();

		////////////////////SPHERE RENDERING////////////////////////
		
		//Use the shader that we calculated at previous frame// 
		if (checker % 2 == 0) {
			glUseProgram(programID2);
		}
		else {
			glUseProgram(programID1);
		}
		///Calculate the shader tha we want
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			if (checker % 2 == 0) {
				glUseProgram(programID1);
			}
			else {
				glUseProgram(programID2);
			}
			checker++;
		}
		
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		
		//Sphere Movement
		//X+
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			xpos1 = xpos1 + 0.1f;
		}
		//X-
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			xpos1 = xpos1 - 0.1f;;
		}
		//Y+
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			ypos1 = ypos1 + 0.1f;
		}
		//Y-
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			ypos1 = ypos1 - 0.1f;
		}
		//Z+
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			zpos1 = zpos1 + 0.1f;
		}
		//Z-
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
			zpos1 = zpos1 - 0.1f;
		}
		
		glm::mat4 ModelMatrix1 = glm::mat4(1.0);
		ModelMatrix1 = glm::translate(ModelMatrix1, glm::vec3(xpos1, ypos1, zpos1));
		ModelMatrix1 = glm::scale(ModelMatrix1, glm::vec3(15.0f, 15.0f, 15.0f));
		glm::mat4 MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			if (checker % 2 == 0) {
				glUseProgram(programID1);
			}
			else {
				glUseProgram(programID2);
			}
			checker++;
		}
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP1[0][0]);
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &MVP1[0][0]);
		
		//Color
		glUniform4f(mycolorID, 1.0, 0.0, 0.0, 1.0);
		
		//Texture
		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Spherevertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : uvs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, Sphereuvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// 3nd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, Spherenormalbuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisable(GL_DEPTH_TEST);

		////////////// END OF SPHERE RENDERING /////////////////////

		////////////////// RENDERING RANDOM OBJECTS////////////////////
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
			srand(time(0));
			GLfloat randompick,randomd;
			randompick = rand() % 3;
			randomd    = rand() % 11;		
			if (randompick == 0) {
				//////////////////Render Cylinder///////////////////
				// Use our shader
				GLfloat redcylinder, greencylinder, bluecylinder,Vx,Vy,Vz;
				redcylinder   = (GLfloat)rand() / RAND_MAX;
				greencylinder = (GLfloat)rand() / RAND_MAX;
				bluecylinder  = (GLfloat)rand() / RAND_MAX;
				Vx = rand() % 2;
				Vy = rand() % 2;
				Vz = rand() % 2;
				glUseProgram(programID1);
				
				glEnable(GL_DEPTH_TEST);

				glm::mat4 ModelMatrix2 = glm::mat4(1.0);
				ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(0.0f, 0.0f, 0.0f));
				ModelMatrix2 = glm::scale(ModelMatrix2, glm::vec3(randomd, randomd, randomd));
				
				// Compute the MVP matrix
				glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
	
				// Send our transformation to the currently bound shader, 
				// in the "MVP" uniform
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
				
				//Color
				glUniform4f(mycolorID, redcylinder, greencylinder, bluecylinder, 1.0);

		 		// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, Cylindervertexbuffer);
				glVertexAttribPointer(
					0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);

				// 2nd attribute buffer : colors
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, Cylinderuvbuffer);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					2,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				// 3nd attribute buffer : colors
				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, Cylindernormalbuffer);
				glVertexAttribPointer(
					2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				// Draw the triangle !
				glDrawArrays(GL_TRIANGLES, 0, vertices1.size());
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
				glDisable(GL_DEPTH_TEST);
			}
			if (randompick == 1) {
					
				////////////////////Render Sphere//////////////////////
				GLfloat redsphere, greensphere, bluesphere,Vx1,Vy1,Vz1;
				redsphere   = (GLfloat)rand() / RAND_MAX;
				greensphere = (GLfloat)rand() / RAND_MAX;
				bluesphere  = (GLfloat)rand() / RAND_MAX;
				Vx1 = rand() % 2;
				Vy1 = rand() % 2;
				Vz1 = rand() % 2;
				
				glUseProgram(programID1);
					
				glEnable(GL_DEPTH_TEST);
				
				glm::mat4 ModelMatrix3 = glm::mat4(1.0);
				ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(0.0f, 0.0f, 0.0f));
				ModelMatrix3 = glm::scale(ModelMatrix3, glm::vec3(randomd, randomd, randomd));

				// Compute the MVP matrix
				glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;

				// Send our transformation to the currently bound shader, 
				// in the "MVP" uniform
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
			
				//Color
				glUniform4f(mycolorID, redsphere, greensphere, bluesphere, 1.0);

				// 1st attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, Spherevertexbuffer);
				glVertexAttribPointer(
					0,								  // attribute. No particular reason for 0, but must match the layout in the shader.
					3,								  // size
					GL_FLOAT,						  // type
					GL_FALSE,						  // normalized?
					0,								  // stride
					(void*)0						  // array buffer offset
				);
	
				// 2nd attribute buffer : colors
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, Sphereuvbuffer);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					2,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				// 3nd attribute buffer : colors
				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, Spherenormalbuffer);
				glVertexAttribPointer(
					2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				// Draw the triangles !
				glDrawArrays(GL_TRIANGLES, 0, vertices.size());
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
				glDisable(GL_DEPTH_TEST);
			}
			else if(randompick==2){
				//////////////////Render Cube////////////////////////////

				// Use our shader
				GLfloat redcube, greencube, bluecube,Vx2,Vy2,Vz2;
				redcube   = (GLfloat)rand() / RAND_MAX;
				greencube = (GLfloat)rand() / RAND_MAX;
				bluecube  = (GLfloat)rand() / RAND_MAX;
				Vx2 = rand() % 2;
				Vy2 = rand() % 2;
				Vz2 = rand() % 2;
				glUseProgram(programID1);

				glm::mat4 ModelMatrix4 = glm::mat4(1.0);
				ModelMatrix4 = glm::scale(ModelMatrix4, glm::vec3(randomd, randomd, randomd));
				
				//Color
				GLuint colorbuffer1 = glGetUniformLocation(programID1, "color");
				glUniform4f(mycolorID, redcube, greencube, bluecube, 1.0);
	
				// Compute the MVP matrix
				glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix4;

				// Send our transformation to the currently bound shader, 
				// in the "MVP" uniform
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);

				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
				glVertexAttribPointer(
					0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
					
				// 2nd attribute buffer : colors
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);

				//// Draw the triangle !
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
			}

		}
		/////////////////END OF RENDERING RANDOM OBJECTS////////////////////////

		////////////////////CUBE RENDERING////////////////////////////////////

		// Use our shader
		glUseProgram(programID);

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		///////////// END OF CUBE RENDERING /////////////////////////////////////
	}
	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &Spherevertexbuffer);
	glDeleteBuffers(1, &Sphereuvbuffer);
	glDeleteBuffers(1, &Cylindervertexbuffer);
	glDeleteBuffers(1, &Cylinderuvbuffer);
	glDeleteProgram(programID);
	glDeleteProgram(programID1);
	glDeleteProgram(programID2);
	
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

