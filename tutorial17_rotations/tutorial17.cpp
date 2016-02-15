// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

// Include AntTweakBar
#include <AntTweakBar.h>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards

#include <iostream>


vec3 gPosition1( 0.0f, 0.0f, 0.0f);
quat gOrientation1;

vec3 gPosition2( 1.0f, 0.0f, 0.0f);
quat gOrientation2;

vec3 cameraPosition(0, 0.8, 6);
quat cameraOrientation;


bool gLookAtOther = false;
bool third_person = false;

int window_width = 1024, window_height = 768;


#include "bone.h"
#include "bone.cpp"


GLsizei indices_count;
GLuint MatrixID, ModelMatrixID, ViewMatrixID;


void init_vars() {
	std::cout << "init-ing vars\n\n";
	glm::vec3 angles(0, 180, 0);
	glm::quat rotation(radians(angles));
	gOrientation2 = gOrientation2 * rotation;
}

void draw_bone(Bone bone, mat4 ProjectionMatrix, mat4 ViewMatrix){
    mat4 ModelMatrix = bone.get_model_matrix();

    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        indices_count,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
}

void draw_skelton(Bone root, mat4 ProjectionMatrix, mat4 ViewMatrix){
    // draw itself
    draw_bone(root, ProjectionMatrix, ViewMatrix);
    int children_count = root.children.size();
    std::cout<<"Children: "<<children_count<<std::endl;
    for(int i=0; i<children_count; i++){
        Bone bone = *root.children[i];
        draw_skelton(bone, ProjectionMatrix, ViewMatrix);
    }

}

int main( void )
{
	init_vars();
	printf("Starting...\n");

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(window_width, window_height, "Cian - Rotations", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(1024, 768);
//	TwBar * EulerGUI = TwNewBar("Euler Obj #1");
	TwBar * QuaternionGUI = TwNewBar("Quaternion Obj #2");
	TwBar * CameraGUI = TwNewBar("Camera Quat settings");


	//cameraOrientation
//	TwSetParam(EulerGUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
	TwSetParam(QuaternionGUI, NULL, "position", TW_PARAM_CSTRING, 1, "808 16");

//	TwAddVarRW(EulerGUI, "Euler X", TW_TYPE_FLOAT, &gOrientation1_degree.x, "step=1");
//	TwAddVarRW(EulerGUI, "Euler Y", TW_TYPE_FLOAT, &gOrientation1_degree.y, "step=1");
//	TwAddVarRW(EulerGUI, "Euler Z", TW_TYPE_FLOAT, &gOrientation1_degree.z, "step=1");
//	TwAddVarRW(EulerGUI, "Pos X"  , TW_TYPE_FLOAT, &gPosition1.x, "step=0.05");
//	TwAddVarRW(EulerGUI, "Pos Y"  , TW_TYPE_FLOAT, &gPosition1.y, "step=0.05");
//	TwAddVarRW(EulerGUI, "Pos Z"  , TW_TYPE_FLOAT, &gPosition1.z, "step=0.05");


	TwAddVarRW(QuaternionGUI, "Quaternion", TW_TYPE_QUAT4F, &gOrientation2, "showval=true open");
	// TwAddSeparator(QuaternionGUI, "sep1", NULL);

	TwAddVarRW(CameraGUI, "Quaternion", TW_TYPE_QUAT4F, &cameraOrientation, "showval=true open");
	TwAddVarRW(CameraGUI, "3rd Person", TW_TYPE_BOOL8, &third_person, "help='Toggle 3rd Person'");



	// TwAddVarRW(QuaternionGUI, "Use LookAt", TW_TYPE_BOOL8 , &gLookAtOther, "help='Look at the other monkey ?'");

	// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);             // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.dds");
	//GLuint Texture;
	//load_texture("uvmap.png", &Texture);

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("dolphin90.obj", vertices, uvs, normals);


	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;

    indices_count = indices.size();

    Bone root = Bone(vec3(0, 0, 0), gPosition1, vec3(1, 1, 1), "Root");
    root.is_root = true;
    Bone bone2 = Bone(vec3(0, 90, 0), gPosition2, vec3(0.5, 0.5, 0.5), "Bone2");
    Bone bone3 = Bone(vec3(0, 90, 0), gPosition1+vec3(1,1,0), vec3(1, 1, 1), "Bone3");
    bone2.add_child(&bone3);
    root.add_child(&bone2);



	do{

		// Measure speed
		double currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastFrameTime);
		lastFrameTime = currentTime;
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID,  // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Set light pos
		glm::vec3 lightPos = glm::vec3(4,5,5);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 ViewMatrix = glm::lookAt(
				cameraPosition, // Camera is here
				glm::vec3(0, 0, 0), // and looks here
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);






		float rotate_angle = 1.0f; // degree

		glm::vec3 angles(0, 0, 0);

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			angles = vec3(0, rotate_angle, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			angles = vec3(0, -rotate_angle, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			angles = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			angles = vec3(rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			angles = vec3(0, 0, -rotate_angle);
		}
		else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			angles = vec3(0, 0, rotate_angle);
		}

		glm::quat rotation(radians(angles));
		cameraOrientation = cameraOrientation * rotation;

		glm::mat4 ViewRotationMatrix = toMat4(cameraOrientation);

		if (third_person) {
			ViewMatrix = ViewMatrix * ViewRotationMatrix;
		}
		else {
			ViewMatrix = ViewRotationMatrix * ViewMatrix;
		}


		{ // Quaternion

			glm::vec3 angles(0, 0, 0);

			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
				angles = vec3(0, -rotate_angle, 0);
			}
			else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				angles = vec3(0, rotate_angle, 0);
			}
			else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
				angles = vec3(rotate_angle, 0, 0);
			}
			else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
				angles = vec3(-rotate_angle, 0, 0);
			}
			else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
				angles = vec3(0, 0, rotate_angle);
			}
			else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
				angles = vec3(0, 0, -rotate_angle);
			}


            root.update(angles, vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f));
            draw_skelton(root, ProjectionMatrix, ViewMatrix);

            // 2nd obj




//            // Apply rotations and convert to mat4
//            angles = vec3(0, 90.0f, 0);
//			rotation = glm::quat(radians(angles));
//			gOrientation2 = gOrientation2 * rotation;
//			gOrientation2 = rotation;
//			RotationMatrix = toMat4(gOrientation2);
//
//
//			TranslationMatrix = translate(mat4(), gPosition2);
//			ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
//
//            ModelMatrix = ModelMatrix * TranslationMatrix * RotationMatrix * ScalingMatrix;
//            //ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
//
//			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
//
//			// Send our transformation to the currently bound shader,
//			// in the "MVP" uniform
//			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
//			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
//
//
//
//
//
//
//			// Draw the triangles !
//			glDrawElements(
//				GL_TRIANGLES,      // mode
//				indices.size(),    // count
//				GL_UNSIGNED_SHORT,   // type
//				(void*)0           // element array buffer offset
//			);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Draw GUI
		TwDraw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);

	// Close GUI and OpenGL window, and terminate GLFW
	TwTerminate();
	glfwTerminate();

	return 0;
}

