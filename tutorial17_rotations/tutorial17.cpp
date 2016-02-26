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

#include "bone.h"
#include "bone.cpp"

#include "skelton.h"
#include "skelton.cpp"



vec3 gPosition1( 0.0f, 0.0f, 0.0f);
quat gOrientation1;

vec3 gPosition2( 1.0f, 0.0f, 0.0f);
quat gOrientation2;

vec3 cameraPosition(0, 0.8, 6);
quat cameraOrientation;


bool gLookAtOther = false;
bool third_person = true;

int window_width = 1024, window_height = 768;


bool control_finger1 = false;
bool control_finger2 = true;
bool control_finger3 = false;
bool control_finger4 = false;
bool control_finger5 = false;
bool animate_hand    = false;



// GL VARS
GLuint vertexPosition_modelspaceID;
GLuint vertexUVID;
GLuint vertexNormal_modelspaceID;
GLuint programID;

GLuint TextureID;
GLuint Texture;

GLsizei indices_count;
GLuint MatrixID, ModelMatrixID, ViewMatrixID;


void init_gui();
void init_vars();
int init_gl();


int main( void )
{
	init_vars();
	printf("Starting...\n");

    int r = init_gl();
    if(r!=0){
        return r;
    }
	init_gui();

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	// bool res = loadOBJ("dolphin90.obj", vertices, uvs, normals);
	bool res = loadOBJ("Bone.obj", vertices, uvs, normals);
	if(!res){
        std::cout<<"Error reading obj\n\n";
        return -1;
	}


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


    vec3 bend_angles = vec3(-15, 0, 0);



    Bone palm("0_palm");
    palm.mPos = vec3(-1,0,0);
    palm.mScale = vec3(1,1,1);






    // Finger 1
    Bone base1("1_Base");
    base1.mScale = vec3(0.3,0.3,0.3);
    base1.mPos = vec3(0.15, 0, 0.1);
    base1.update_by_angle(vec3(0, 90, 60));

    Bone mid1("1_Mid");
    mid1.mPos = vec3(0,0,2);

    Bone tip1("1_Tip");
    tip1.mPos = vec3(0,0,2);

    palm.add_child(&base1);
    base1.add_child(&mid1);
    mid1.add_child(&tip1);

    // Finger 2
    Bone base2("2_Base");
    base2.mScale = vec3(0.3,0.3,0.3);
    base2.mPos = vec3(0.15, 0, 0.7);
    base2.update_by_angle(vec3(0, 90, 60));

    Bone mid2("2_Mid");
    mid2.mPos = vec3(0,0,2);

    Bone tip2("2_Tip");
    tip2.mPos = vec3(0,0,2);

    palm.add_child(&base2);
    base2.add_child(&mid2);
    mid2.add_child(&tip2);

    // Finger 3
    Bone base3("3_Base");
    base3.mScale = vec3(0.3,0.3,0.3);
    base3.mPos = vec3(0.15, 0, 1.3);
    base3.update_by_angle(vec3(0, 90, 60));

    Bone mid3("3_Mid");
    mid3.mPos = vec3(0,0,2);

    Bone tip3("3_Tip");
    tip3.mPos = vec3(0,0,2);

    palm.add_child(&base3);
    base3.add_child(&mid3);
    mid3.add_child(&tip3);

    // Finger 4
    Bone base4("4_Base");
    base4.mScale = vec3(0.3,0.3,0.3);
    base4.mPos = vec3(0.15, 0, 1.9);
    base4.update_by_angle(vec3(0, 90, 60));

    Bone mid4("4_Mid");
    mid4.mPos = vec3(0,0,2);

    Bone tip4("4_Tip");
    tip4.mPos = vec3(0,0,2);

    palm.add_child(&base4);
    base4.add_child(&mid4);
    mid4.add_child(&tip4);

    // Thumb 1
    Bone base5("5_Base");
    base5.mScale = vec3(0.25,0.25,0.25);
    base5.mPos = vec3(-0.15, 0, 0.3);
    base5.update_by_angle(vec3(-65, 90, 60));

    Bone mid5("5_Mid");
    mid5.mPos = vec3(0,0,2);

    Bone tip5("5_Tip");
    tip5.mPos = vec3(0,0,2);








    palm.add_child(&base5);
    base5.add_child(&mid5);
    mid5.add_child(&tip5);

    mid1.update_by_angle(bend_angles);
    tip1.update_by_angle(bend_angles);

    mid2.update_by_angle(bend_angles);
    tip2.update_by_angle(bend_angles);

    mid3.update_by_angle(bend_angles);
    tip3.update_by_angle(bend_angles);

    mid4.update_by_angle(bend_angles);
    tip4.update_by_angle(bend_angles);

    bend_angles *= -1;

    mid5.update_by_angle(bend_angles);
    tip5.update_by_angle(bend_angles);

    // Make hand
    Skelton hand_skelton = Skelton(&palm);
    hand_skelton.MatrixID      = MatrixID;
    hand_skelton.ModelMatrixID = ModelMatrixID;
    hand_skelton.indices_count = indices_count;



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
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



        // Camera
		float rotate_angle = 1.0f; // degree

		glm::vec3 angles_camera(0, 0, 0);

		glm::quat rotation(radians(angles_camera));
		cameraOrientation = cameraOrientation * rotation;

		glm::mat4 ViewRotationMatrix = toMat4(cameraOrientation);

		if (third_person) {
			ViewMatrix = ViewMatrix * ViewRotationMatrix;
		}
		else {
			ViewMatrix = ViewRotationMatrix * ViewMatrix;
		}



        // Models
        glm::vec3 angles_model(0, 0, 0);

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            angles_model = vec3(0, -rotate_angle, 0);
        }
        else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            angles_model = vec3(0, rotate_angle, 0);
        }
        else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            angles_model = vec3(rotate_angle, 0, 0);
        }
        else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            angles_model = vec3(-rotate_angle, 0, 0);
        }
        else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            angles_model = vec3(0, 0, rotate_angle);
        }
        else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            angles_model = vec3(0, 0, -rotate_angle);
        }

        hand_skelton.update_bone("0_palm", angles_model);

        // Base3
        angles_model = vec3(0,0,0);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			angles_model = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			angles_model = vec3(rotate_angle, 0, 0);
		}
        //base1.update_by_angle(angles_model);
        hand_skelton.update_bone("3_Base", angles_model);
        // Mid2
        angles_model = vec3(0,0,0);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			angles_model = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			angles_model = vec3(rotate_angle, 0, 0);
		}
        hand_skelton.update_bone("3_Mid", angles_model);
        // Tip2
        angles_model = vec3(0,0,0);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			angles_model = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			angles_model = vec3(rotate_angle, 0, 0);
		}
        hand_skelton.update_bone("3_Tip", angles_model);


        angles_model = vec3(0,0,0);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			angles_model = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			angles_model = vec3(rotate_angle, 0, 0);
		}


		if(animate_hand){
            float animate_amount = sin(currentTime);
            animate_amount *= 0.3;

            angles_model = vec3(animate_amount, 0, 0);
		}


		if(control_finger1){
            hand_skelton.update_bone("1_Base", angles_model);
            hand_skelton.update_bone("1_Mid", angles_model);
            hand_skelton.update_bone("1_Tip", angles_model);
		}
		if(control_finger2){
            hand_skelton.update_bone("2_Base", angles_model);
            hand_skelton.update_bone("2_Mid", angles_model);
            hand_skelton.update_bone("2_Tip", angles_model);
		}
		if(control_finger3){
            hand_skelton.update_bone("3_Base", angles_model);
            hand_skelton.update_bone("3_Mid", angles_model);
            hand_skelton.update_bone("3_Tip", angles_model);
		}
		if(control_finger4){
            hand_skelton.update_bone("4_Base", angles_model);
            hand_skelton.update_bone("4_Mid", angles_model);
            hand_skelton.update_bone("4_Tip", angles_model);
		}
		if(control_finger5){
            // Thumb
            hand_skelton.update_bone("5_Base", -angles_model);
            hand_skelton.update_bone("5_Mid", -angles_model);
            hand_skelton.update_bone("5_Tip", -angles_model);
		}




        hand_skelton.render(ProjectionMatrix, ViewMatrix);




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


int init_gl(){

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
	programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");
	vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Load the texture
	Texture = loadDDS("bone.dds");

	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    return 0;
}

void init_vars() {
	std::cout << "init-ing vars\n\n";
	glm::vec3 angles(0, 180, 0);
	glm::quat rotation(radians(angles));
	gOrientation2 = gOrientation2 * rotation;
}

void init_gui(){

	// Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(1024, 768);
//	TwBar * EulerGUI = TwNewBar("Euler Obj #1");
	TwBar * HandGUI = TwNewBar("Hand Movements");
	TwBar * CameraGUI = TwNewBar("Camera Quat settings");


	//Hand GUI
	TwSetParam(HandGUI, NULL, "position", TW_PARAM_CSTRING, 1, "808 16");
    TwAddVarRW(HandGUI, "Index Finger", TW_TYPE_BOOL8, &control_finger1, "help='Toggle 3rd Person'");
    TwAddVarRW(HandGUI, "Middle Finger", TW_TYPE_BOOL8, &control_finger2, "help='Toggle 3rd Person'");
    TwAddVarRW(HandGUI, "Rign Finger", TW_TYPE_BOOL8, &control_finger3, "help='Toggle 3rd Person'");
    TwAddVarRW(HandGUI, "Baby Finger", TW_TYPE_BOOL8, &control_finger4, "help='Toggle 3rd Person'");
    TwAddVarRW(HandGUI, "Thumb", TW_TYPE_BOOL8, &control_finger5, "help='Toggle 3rd Person'");

	TwAddSeparator(HandGUI, "sep1", NULL);
    TwAddVarRW(HandGUI, "Animate", TW_TYPE_BOOL8, &animate_hand, "help='Toggle 3rd Person'");


    // Camera
	TwAddVarRW(CameraGUI, "Quaternion", TW_TYPE_QUAT4F, &cameraOrientation, "showval=true open");
	TwAddVarRW(CameraGUI, "3rd Person", TW_TYPE_BOOL8, &third_person, "help='Toggle 3rd Person'");



	// TwAddVarRW(QuaternionGUI, "Use LookAt", TW_TYPE_BOOL8 , &gLookAtOther, "help='Look at the other monkey ?'");

	// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);             // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar
}
