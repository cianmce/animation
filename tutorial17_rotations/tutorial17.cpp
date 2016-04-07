// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       /* time */

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

#include "apple.h"
#include "apple.cpp"



vec3 gPosition1( 0.0f, 0.0f, 0.0f);
quat gOrientation1;

vec3 gPosition2( 1.0f, 0.0f, 0.0f);
quat gOrientation2;

vec3 cameraPosition(0, 5.8, 33);
quat cameraOrientation;

vec3 apple_position(1, 5, 1);
bool apple_falling = false;
float apple_velocity = 0;
vec3 apple_scale = vec3(1,1,1);
float apple_mass = 20; // kg
float Cd = 0.47; // Drag coefficient of Sphere
float apple_area = 3.14;
float rho = 0;


/*
rho
    name: "Vacuum",
    mag: 0
}, {
    name: "Air",
    mag: 1.225
}, {
    name: "Water",
    mag: 1000
}, {
    name: "Mercury",
    mag: 13534

*/

float coefficient_of_restitution = 0.99;

float gravity = 9.81;


vec3 floor_position = vec3(0, -15, 0);



vec3 rope_position = vec3(1.0);

vec3 scale_rope = vec3(0.15, 5, 0.15);

bool animate_camera = false;
bool look_at_apple = true;


bool gLookAtOther = false;
bool third_person = true;

// int window_width = 1024, window_height = 768;
// int window_width = 1366, window_height = 768; // laptop
 int window_width = 1280, window_height = 1024; // monitor home
//int window_width = 1680, window_height = 1050; // monitor college

bool done = false;

int animation_number  = 0;
bool pause_ik         = true;
bool animate_curve    = false;
bool animate_hit      = false;
double start_hit_time = 0;
double total_hit_time = 2.0;
vec3 hit_p0 = vec3(0, 0, -5);
vec3 hit_p1 = vec3(0, 1, 1);
vec3 hit_p2 = vec3(0, 1, 1);
vec3 hit_p3 = vec3(0, 0, 5);


bool chopped = false;


float animation_section_time = 2.0f; // seconds
std::vector<glm::vec3> hand_animations;
std::vector<glm::vec3> camera_animation;


// Apples
std::vector<Apple> apples;
int num_apples = 10;


void gen_rand_apples(){
    srand (time(NULL));
    for(int i=0; i<num_apples; i++){
        Apple a = Apple();
        a.x = (rand() % 200 + 1) / 10.0f;
        a.y = 12+(rand() % 200 + 1) / 10.0f;
        a.z = (rand() % 200 + 1) / 10.0f;
        apples.push_back(a);
    }

}


// Link files
/*
ln -s /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial17_rotations/*.dds /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin
ln -s /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial17_rotations/*.obj /home/cian/College/Animation/OpenGL_tut/ogl-OpenGL-tutorial_0015_33/tutorial_bin
*/

void init_animinations(){

	camera_animation.push_back(vec3(0, 5, 33)); // p0
    camera_animation.push_back(vec3(0,-2,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(15, 6, 15)); // p3


    camera_animation.push_back(vec3(15, 6, 15)); // p0
    camera_animation.push_back(vec3(0,6,0)); // p1
    camera_animation.push_back(vec3(0,8,0)); // p2
    camera_animation.push_back(vec3(33, 4, 0)); // p3


    camera_animation.push_back(vec3(33, 4, 0)); // p0
    camera_animation.push_back(vec3(0,8,0)); // p1
    camera_animation.push_back(vec3(0,6,0)); // p2
    camera_animation.push_back(vec3(15, 7, -15)); // p3


    camera_animation.push_back(vec3(15, 7, -15)); // p0
    camera_animation.push_back(vec3(0,0,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(0,9, -33)); // p3



    camera_animation.push_back(vec3(0,9, -33)); // p0
    camera_animation.push_back(vec3(0,0,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(-15, 12, -15)); // p3


    camera_animation.push_back(vec3(-15, 12, -15)); // p0
    camera_animation.push_back(vec3(0,0,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(-35, 15, 0)); // p3


    camera_animation.push_back(vec3(-35, 15, 0)); // p0
    camera_animation.push_back(vec3(0,0,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(-15, 8, 15)); // p3


    camera_animation.push_back(vec3(-15, 8, 15)); // p0
    camera_animation.push_back(vec3(0,0,0)); // p1
    camera_animation.push_back(vec3(0,0,0)); // p2
    camera_animation.push_back(vec3(0, 5, 33)); // p3




//
//
//    hand_animations.push_back(vec3(0, 0, 0)); // p0
//    hand_animations.push_back(vec3(0,1,0)); // p1
//    hand_animations.push_back(vec3(0,1,0)); // p2
//    hand_animations.push_back(vec3(0, 2, 5)); // p3
//
//
//    hand_animations.push_back(vec3(0, 2, 5)); // p0
//    hand_animations.push_back(vec3(0,3,0)); // p1
//    hand_animations.push_back(vec3(0,4,0)); // p2
//    hand_animations.push_back(vec3(-5, 5, 0)); // p3
//
//
//    hand_animations.push_back(vec3(-5, 5, 0)); // p0
//    hand_animations.push_back(vec3(0,0,0)); // p1
//    hand_animations.push_back(vec3(0,0,0)); // p2
//    hand_animations.push_back(vec3(0, 6, -5)); // p3
//
//
//    hand_animations.push_back(vec3(0, 6, -5)); // p0
//    hand_animations.push_back(vec3(0,0,0)); // p1
//    hand_animations.push_back(vec3(0,0,0)); // p2
//    hand_animations.push_back(vec3(5, 5, 0)); // p3
//
//
//    hand_animations.push_back(vec3(5, 5, 0)); // p0
//    hand_animations.push_back(vec3(0,0,0)); // p1
//    hand_animations.push_back(vec3(0,0,0)); // p2
//    hand_animations.push_back(vec3(0, 2, 5)); // p3
//
//
//    hand_animations.push_back(vec3(0, 2, 5)); // p0
//    hand_animations.push_back(vec3(0,0,0)); // p1
//    hand_animations.push_back(vec3(0,0,0)); // p2
//    hand_animations.push_back(vec3(0, 0, 0)); // p3


    hand_animations.push_back(vec3(0, 0, 0)); // p0
    hand_animations.push_back(vec3(0,1,0)); // p1
    hand_animations.push_back(vec3(0,1,0)); // p2
    hand_animations.push_back(vec3(0, 2, 5)); // p3


    hand_animations.push_back(vec3(0, 2, 5)); // p0
    hand_animations.push_back(vec3(0,3,0)); // p1
    hand_animations.push_back(vec3(0,4,0)); // p2
    hand_animations.push_back(vec3(0, 5, -5)); // p3


    hand_animations.push_back(vec3(0, 5, -5)); // p0
    hand_animations.push_back(vec3(0,6,0)); // p1
    hand_animations.push_back(vec3(0,6,0)); // p2
    hand_animations.push_back(vec3(-5, 6, 0)); // p3


    hand_animations.push_back(vec3(-5, 6, 0)); // p0
    hand_animations.push_back(vec3(0,4,0)); // p1
    hand_animations.push_back(vec3(0,5,0)); // p2
    hand_animations.push_back(vec3(5, 5, 0)); // p3


    hand_animations.push_back(vec3(5, 5, 0)); // p0
    hand_animations.push_back(vec3(0,3,0)); // p1
    hand_animations.push_back(vec3(0,2,0)); // p2
    hand_animations.push_back(vec3(0, 2, 5)); // p3


    hand_animations.push_back(vec3(0, 2, 5)); // p0
    hand_animations.push_back(vec3(0,1,0)); // p1
    hand_animations.push_back(vec3(0,1,0)); // p2
    hand_animations.push_back(vec3(0, 0, 0)); // p3








}



// GL VARS
GLuint vertexPosition_modelspaceID;
GLuint vertexUVID;
GLuint vertexNormal_modelspaceID;
GLuint programID;

GLuint TextureID;
GLuint Texture;
GLuint Texture_apple;
GLuint Texture_rope;

GLsizei indices_count;
GLsizei indices_count_apple;
GLsizei indices_count_rope;
GLuint MatrixID, ModelMatrixID, ViewMatrixID;


void init_gui();
void init_vars();
int init_gl();
float distance_to();


bool use_hermite = false;

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline
// bool to chose type
vec3 curve(float t, vec3 p0, vec3 p1, vec3 p2, vec3 p3){
    if(use_hermite){
        return ( pow( (1-t), 3) * p0 ) + ( 3*t*pow( (1-t), 2) * p1 ) + ( 3*t*pow( (1-t), 2) * p2 ) + ( pow(t, 3) * p3 );
    }else{
        std::cout<<"input: " << t <<" \n"<< glm::to_string(p0) << "\n"<< glm::to_string(p1) << "\n"<< glm::to_string(p2) << "\n"<< glm::to_string(p3) << "\n";
        // return ( pow( (1-t), 2) * p0 ) + ( 2 * t * (1-t) * p1 ) + ( pow(t, 2) * p3 );
        return ( 2*t*t*t - 3*t*t + 1)*p0 + (t*t*t - 2*t*t + t)*p1 + ( -2*t*t*t + 3*t*t )*p3 + ( t*t*t - t*t )*p2;
    }
}

void go(){
    pause_ik = false;
    animate_curve = true;

    gen_rand_apples();
}


int main( void )
{
	init_vars();
	init_animinations();
	printf("Starting...\n");

    int r = init_gl();
    if(r!=0){
        return r;
    }
	init_gui();

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> vertices_apple;
	std::vector<glm::vec3> vertices_rope;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec2> uvs_apple;
	std::vector<glm::vec2> uvs_rope;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> normals_apple;
	std::vector<glm::vec3> normals_rope;
	// bool res = loadOBJ("dolphin90.obj", vertices, uvs, normals);
	bool res = loadOBJ("Bone.obj", vertices, uvs, normals);
	if(!res){
        std::cout<<"Error reading bone obj\n\n";
        return -1;
	}

	res = loadOBJ("apple.obj", vertices_apple, uvs_apple, normals_apple);
	if(!res){
        std::cout<<"Error reading apple obj\n\n";
        return -1;
	}

	res = loadOBJ("rope.obj", vertices_rope, uvs_rope, normals_rope);
	if(!res){
        std::cout<<"Error reading rope obj\n\n";
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

    indices_count = indices.size();






	std::vector<unsigned short> indices_apple;
	std::vector<glm::vec3> indexed_vertices_apple;
	std::vector<glm::vec2> indexed_uvs_apple;
	std::vector<glm::vec3> indexed_normals_apple;

	indexVBO(vertices_apple, uvs_apple, normals_apple, indices_apple, indexed_vertices_apple, indexed_uvs_apple, indexed_normals_apple);

	// Load it into a VBO

	GLuint vertexbuffer_apple;
	glGenBuffers(1, &vertexbuffer_apple);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_apple);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices_apple.size() * sizeof(glm::vec3), &indexed_vertices_apple[0], GL_STATIC_DRAW);

	GLuint uvbuffer_apple;
	glGenBuffers(1, &uvbuffer_apple);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_apple);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs_apple.size() * sizeof(glm::vec2), &indexed_uvs_apple[0], GL_STATIC_DRAW);

	GLuint normalbuffer_apple;
	glGenBuffers(1, &normalbuffer_apple);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_apple);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals_apple.size() * sizeof(glm::vec3), &indexed_normals_apple[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
	GLuint elementbuffer_apple;
	glGenBuffers(1, &elementbuffer_apple);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_apple);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_apple.size() * sizeof(unsigned short), &indices_apple[0] , GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID_apple = glGetUniformLocation(programID, "LightPosition_worldspace");

    indices_count_apple = indices_apple.size();







	std::vector<unsigned short> indices_rope;
	std::vector<glm::vec3> indexed_vertices_rope;
	std::vector<glm::vec2> indexed_uvs_rope;
	std::vector<glm::vec3> indexed_normals_rope;

	indexVBO(vertices_rope, uvs_rope, normals_rope, indices_rope, indexed_vertices_rope, indexed_uvs_rope, indexed_normals_rope);

	// Load it into a VBO

	GLuint vertexbuffer_rope;
	glGenBuffers(1, &vertexbuffer_rope);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_rope);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices_rope.size() * sizeof(glm::vec3), &indexed_vertices_rope[0], GL_STATIC_DRAW);

	GLuint uvbuffer_rope;
	glGenBuffers(1, &uvbuffer_rope);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_rope);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs_rope.size() * sizeof(glm::vec2), &indexed_uvs_rope[0], GL_STATIC_DRAW);

	GLuint normalbuffer_rope;
	glGenBuffers(1, &normalbuffer_rope);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_rope);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals_rope.size() * sizeof(glm::vec3), &indexed_normals_rope[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
	GLuint elementbuffer_rope;
	glGenBuffers(1, &elementbuffer_rope);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_rope);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_rope.size() * sizeof(unsigned short), &indices_rope[0] , GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID_rope = glGetUniformLocation(programID, "LightPosition_worldspace");

    indices_count_rope = indices_rope.size();









	// For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;


    float bone_scale = 1.0;
    Bone base0("0_Base");
    base0.mPos = vec3(0,0,0);
    base0.mScale = vec3(bone_scale);

    Bone mid0("0_Mid");
    mid0.mPos = vec3(0, 0, 2);


    Bone hand0("0_Hand");
    hand0.mPos = vec3(0, 0, 2);



    Bone finger0("0_Finger0");
    finger0.mPos = vec3(-0.3, 0, 2);
    finger0.mScale = vec3(0.5);

    Bone finger01("0_Finger01");
    finger01.mPos = vec3(0, 0, 2);
    finger01.mScale = vec3(0.5);

    Bone finger02("0_Finger02");
    finger02.mPos = vec3(0.3, 0, 2);
    finger02.mScale = vec3(0.5);

    Bone finger03("0_Finger03");
    finger03.mPos = vec3(0.6, 0, 2);
    finger03.mScale = vec3(0.5);

    // thumb
    Bone finger04("0_Finger04");
    finger04.mPos = vec3(0, 0.4, 2);
    finger04.mScale = vec3(0.5);



    Bone finger1("0_Finger1");
    finger1.mPos = vec3(0, 0, 2);

    Bone finger11("0_Finger11");
    finger11.mPos = vec3(0, 0, 2);

    Bone finger12("0_Finger12");
    finger12.mPos = vec3(0, 0, 2);

    Bone finger13("0_Finger13");
    finger13.mPos = vec3(0, 0, 2);

    Bone finger14("0_Finger14");
    finger14.mPos = vec3(0, 0, 2);



    Bone finger2("0_Finger2");
    finger2.mPos = vec3(0, 0, 2);

    Bone finger21("0_Finger21");
    finger21.mPos = vec3(0, 0, 2);

    Bone finger22("0_Finger22");
    finger22.mPos = vec3(0, 0, 2);

    Bone finger23("0_Finger23");
    finger23.mPos = vec3(0, 0, 2);

    Bone finger24("0_Finger24");
    finger24.mPos = vec3(0, 0, 2);



    finger1.add_child(&finger2);
    finger11.add_child(&finger21);
    finger12.add_child(&finger22);
    finger13.add_child(&finger23);
    finger14.add_child(&finger24);

    finger0.add_child(&finger1);
    finger01.add_child(&finger11);
    finger02.add_child(&finger12);
    finger03.add_child(&finger13);
    finger04.add_child(&finger14);

    hand0.add_child(&finger0);
    hand0.add_child(&finger01);
    hand0.add_child(&finger02);
    hand0.add_child(&finger03);
    hand0.add_child(&finger04);

    mid0.add_child(&hand0);
    base0.add_child(&mid0);






    // Make hand
    Skelton hand_skelton = Skelton(&base0);
    hand_skelton.MatrixID      = MatrixID;
    hand_skelton.ModelMatrixID = ModelMatrixID;
    hand_skelton.indices_count = indices_count;

    hand_skelton.point_to(vec3(4,4,4));

	do{

        // Measure speed
		double currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastFrameTime);

        // Fix gui vars
        if(coefficient_of_restitution <= 0){
            coefficient_of_restitution = 0.01;
        }


		lastFrameTime = currentTime;
		nbFrames++;
		if ( currentTime - lastTime >= 1.0){ // If last prinf() was more than 1sec ago
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

        if(animate_camera){

            float animation_count = camera_animation.size() / 4.0f; // 4 per curve
            float animation_time = animation_section_time * animation_count;

            float t = glm::mod( (float)currentTime, animation_time ) / (animation_time / animation_count);
            std::cout << "currentTime: "<< t <<"\n";
            int animation_index = t;
            animation_index *= 4; // start index
            std::cout << "animation_index: "<< animation_index <<"\n";

            t = glm::mod(t, 1.0f);
            std::cout << "fraction: "<< t <<"\n";

            cameraPosition = curve( t,
                                    camera_animation[animation_index],
                                    camera_animation[animation_index+1],
                                    camera_animation[animation_index+2],
                                    camera_animation[animation_index+3]);
        }

        if(look_at_apple){
            ViewMatrix = glm::lookAt(
                    cameraPosition, // Camera is here
                    apple_position, // and looks here
                    glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
                );
        }

        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



        // Camera
		float rotate_angle = 0.01f; // rad

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

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            angles_model = vec3(-rotate_angle, 0, 0);
        }
        else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            angles_model = vec3(rotate_angle, 0, 0);
        }


        hand_skelton.update_bone("0_Finger04", angles_model);
        hand_skelton.update_bone("0_Finger14", 2.0f*angles_model);
        hand_skelton.update_bone("0_Finger24", 3.0f*angles_model);



        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            go();
        }



        vec3 apple_height = vec3(0,2.4,0);
        vec3 target_position = apple_position + apple_height;


        if(animate_curve && !chopped ){
            // First time hitting
            float animation_count = hand_animations.size() / 4.0f; // 4 per curve
            // Total animation time
            float animation_time = 0.2 * animation_section_time * animation_count;

            float t = glm::mod( (float)currentTime, animation_time ) / (animation_time / animation_count);
            std::cout << "currentTime: "<< t <<"\n";
            int animation_index = t;
            animation_index *= 4; // start index
            std::cout << "animation_index: "<< animation_index <<"\n";

            if(animation_index >= 20){
                chopped = true;
            }

            t = glm::mod(t, 1.0f);
            std::cout << "fraction: "<< t <<"\n";

            float scaler = 0.5f;
            target_position = curve( t,
                                        hand_animations[animation_index]*scaler   + apple_position,
                                        hand_animations[animation_index+1]*scaler + apple_position,
                                        hand_animations[animation_index+2]*scaler + apple_position,
                                        hand_animations[animation_index+3]*scaler + apple_position
                                    );


            std::cout<<"apple_position: "<<glm::to_string(apple_position)<<"\n";
            std::cout<<"target_position: "<<glm::to_string(target_position)<<"\n";




            // apple_position = target_position - apple_height;

        }


        float dist = distance(target_position, hand0.end_effector_pos());
        if(pause_ik){
            //target_position = hand0.end_effector_pos();
            //std::cout<<"target_position: "<<glm::to_string(target_position)<<"\n\n";
        }else{

        }



        bool at_it = dist<0.05;
        if((!at_it && !pause_ik) || (animate_curve && !chopped) ){
            hand_skelton.point_to(target_position);
        }

        float dist_to_floor = apple_position.y - floor_position.y;


        // Apple pos
        float move_amount = 0.05;
        if(!apple_falling){
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                apple_position[0] -= move_amount;
            }
            else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                apple_position[0] += move_amount;
            }
            else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                apple_position[2] -= move_amount;
            }
            else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                apple_position[2] += move_amount;
            }
            else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                apple_position[1] += move_amount;
            }
            else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                apple_position[1] -= move_amount;
            }
        }else{
            float apple_velocity_none_zero = (apple_velocity==0.0?0.001:apple_velocity);
            float Fy = -0.5 * Cd * apple_area * rho * apple_velocity*apple_velocity*apple_velocity / glm::abs(apple_velocity_none_zero);
            if(!Fy == Fy){
                Fy = 0;
            }
            float accy = -gravity + Fy / apple_mass;
            // Apple is falling
            apple_velocity += accy * deltaTime;
            apple_position.y += apple_velocity * deltaTime;
            // Check ground
            if (dist_to_floor <= 0){
                std::cout<<"Bouncing speed:"<<apple_velocity<<"\n";
                if(glm::abs(apple_velocity) < 1.7){
                    apple_falling = false;
                    done = true;
                    apple_scale = vec3(1,1,1);
                }
                apple_velocity *= -1.0 * coefficient_of_restitution;
                apple_position.y = floor_position.y+0.01;
            }
        }


        if(!done && apple_falling && ( dist_to_floor < 2 ) && dist_to_floor>0.1){
            // Squash
            apple_scale.y = dist_to_floor/2;
            if(apple_scale.y < 0.2){
                apple_scale.y = 0.2;
            }
            apple_scale.x = 2 - (dist_to_floor/2);
            apple_scale.z = 2 - (dist_to_floor/2);
        }
        //std::cout<<"apple_velocity: "<<apple_velocity<<" Dist: "<<dist_to_floor<<"\n";

        if(!done && apple_falling && 2<dist_to_floor && dist_to_floor<20){
            // stretch
            float a = -0.012345679;
            float b =  0.271604938;
            float c =  0.506172839;
            apple_scale.y = (a*dist_to_floor*dist_to_floor) + b*dist_to_floor + c;
            std::cout<<"\nx="<<dist_to_floor<<"\ty="<<apple_scale.y<<"\n\n";

        }




        angles_model = vec3(0,0,0);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			angles_model = vec3(-rotate_angle, 0, 0);
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			angles_model = vec3(rotate_angle, 0, 0);
		}



        hand_skelton.render(ProjectionMatrix, ViewMatrix);


        // Draw apple
		// Use our shader
		glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture_apple);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_apple);
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
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_apple);
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
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_apple);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_apple);

        // Set light pos
		// glUniform3f(LightID_apple, lightPos.x, lightPos.y, lightPos.z);

        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



        // apple
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = translate(ModelMatrix, apple_position) * scale(mat4(), apple_scale);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

        // draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices_count_apple,    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
        );










        // Draw rope
        // Use our shader
		glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture_rope);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_rope);
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
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_rope);
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
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_rope);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_rope);

        // Set light pos
		// glUniform3f(LightID_apple, lightPos.x, lightPos.y, lightPos.z);

        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



        // rope
		ModelMatrix = glm::mat4(1.0);

		rope_position = apple_position + vec3(0.075, 0.5, 0);

        if(at_it && chopped){
            pause_ik = true;
            if(scale_rope[1] > 0){
               scale_rope[1] -= 0.5;
               rope_position[1] += (10 - (1*scale_rope[1]));
            }else{
                apple_falling = true;
            }
        }


		ModelMatrix = translate(ModelMatrix, rope_position) * scale(mat4(), scale_rope);

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

        // draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices_count_rope,    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
        );






        // Draw floor
        // Use our shader
		glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture_rope);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_rope);
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
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_rope);
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
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_rope);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_rope);

        // Set light pos
		// glUniform3f(LightID_apple, lightPos.x, lightPos.y, lightPos.z);

        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



        // floor
		ModelMatrix = glm::mat4(1.0);

		ModelMatrix = translate(ModelMatrix, floor_position-vec3(0,-0.1,0)) * scale(mat4(), vec3(500, 0.01, 500));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

        // draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices_count_rope,    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
        );









         if(done){
            std::cout<<"\nDONE\n";
            for(int i=0; i<apples.size(); i++){
                if(!apples[i].stopped){
                    float apple_velocity_none_zero = (apples[i].velocity_y==0.0?0.001:apples[i].velocity_y);
                    float Fy = -0.5 * Cd * apple_area * rho * apples[i].velocity_y*apples[i].velocity_y*apples[i].velocity_y / glm::abs(apple_velocity_none_zero);
                    if(!Fy == Fy){
                        Fy = 0;
                    }
                    std::cout<<"#"<<i<<" vel:"<<apples[i].velocity_y<<"\ty:"<<apples[i].y<<"\n";
                    float accy = -gravity + Fy / apple_mass;
                    // Apple is falling
                    apples[i].velocity_y += accy * deltaTime;
                    apples[i].y += apples[i].velocity_y * deltaTime;
                    float dist_to_floor = apples[i].y - floor_position.y;
                    // Check ground
                    if (dist_to_floor <= 0){
                        if(glm::abs(apples[i].velocity_y) < 1.7){
                            apples[i].stopped = true;
                        }
                        apples[i].velocity_y *= -1.0 * coefficient_of_restitution;
                        apples[i].y = floor_position.y+0.01;
                    }





                    if(( dist_to_floor < 2 ) && dist_to_floor>0.1){
                        // Squash
                        apples[i].scale.y = dist_to_floor/2;
                        if(apples[i].scale.y < 0.2){
                            apples[i].scale.y = 0.2;
                        }
                        apples[i].scale.x = 2 - (dist_to_floor/2);
                        apples[i].scale.z = 2 - (dist_to_floor/2);
                    }
                    //std::cout<<"apple_velocity: "<<apple_velocity<<" Dist: "<<dist_to_floor<<"\n";

                    if(2<dist_to_floor && dist_to_floor<20){
                        // stretch
                        float a = -0.012345679;
                        float b =  0.271604938;
                        float c =  0.506172839;
                        apples[i].scale.y = (a*dist_to_floor*dist_to_floor) + b*dist_to_floor + c;
                    }
                }else{
                    apples[i].scale = vec3(1,1,1);
                }
                // Draw apple


                // Draw apple
                // Use our shader
                glUseProgram(programID);

                // Bind our texture in Texture Unit 0
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, Texture_apple);
                // Set our "myTextureSampler" sampler to user Texture Unit 0
                glUniform1i(TextureID, 0);
                // 1rst attribute buffer : vertices
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_apple);
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
                glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_apple);
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
                glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_apple);
                glVertexAttribPointer(
                    vertexNormal_modelspaceID,    // The attribute we want to configure
                    3,                            // size
                    GL_FLOAT,                     // type
                    GL_FALSE,                     // normalized?
                    0,                            // stride
                    (void*)0                      // array buffer offset
                );

                // Index buffer
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_apple);

                // Set light pos
                // glUniform3f(LightID_apple, lightPos.x, lightPos.y, lightPos.z);

                glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



                // apple
                glm::mat4 ModelMatrix = glm::mat4(1.0);
                ModelMatrix = translate(ModelMatrix, vec3( apples[i].x, apples[i].y, apples[i].z ) ) * scale(mat4(), apples[i].scale);
                glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
                glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

                // draw the triangles !
                glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices_count_apple,    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                );





            }
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
//	window = glfwCreateWindow(640, 480, "Cian - Bones", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(window_width, window_height, "Cian - Bones", NULL, NULL);




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
    glfwSetCursorPos(window, window_width/2, window_height/2);

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
	Texture_apple = loadDDS("apple.dds");
	Texture_rope = loadDDS("rope.dds");

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
	TwWindowSize(window_width, window_height);

	TwBar * ToolGUI = TwNewBar("Tools");
	TwDefine("Tools size='220 400' position='10 10' ");
	// TwBar * CameraGUI = TwNewBar("Camera settings");

    // Tools
//	TwAddVarRW(ToolGUI, "Animate Curve", TW_TYPE_BOOL8, &animate_curve, "help='Play Animation'");
	TwAddVarRW(ToolGUI, "Use Hermite", TW_TYPE_BOOL8, &use_hermite, "help='Use hermite curves instead of Bezier'");
//	TwAddVarRW(ToolGUI, "Animation Type", TW_TYPE_INT8, &animation_number, " min=0 max=4");
//	TwAddVarRW(ToolGUI, "Audio Hits", TW_TYPE_BOOL8, &animate_hit, "help='Play Animation when at target'");
	TwAddVarRW(ToolGUI, "Pause IK", TW_TYPE_BOOL8, &pause_ik, "help='Pause IK'");

    TwAddSeparator(ToolGUI, "sep1", NULL);

    TwAddVarRW(ToolGUI, "Coefficient of Restitution", TW_TYPE_FLOAT, &coefficient_of_restitution, "step=0.01");
    TwAddVarRW(ToolGUI, "Apple Mass(kg)", TW_TYPE_FLOAT, &apple_mass, "step=0.01");
    TwAddVarRW(ToolGUI, "Rho", TW_TYPE_FLOAT, &rho, "step=0.01");
    TwAddVarRW(ToolGUI, "Gravity", TW_TYPE_FLOAT, &gravity, "step=0.01");


    TwAddSeparator(ToolGUI, "sep2", NULL);

    TwAddVarRW(ToolGUI, "Number Of Apples", TW_TYPE_INT16, &num_apples, "step=1");



    TwAddSeparator(ToolGUI, "sep3", NULL);


    // Camera
	TwAddVarRW(ToolGUI, "Quaternion", TW_TYPE_QUAT4F, &cameraOrientation, "showval=true open");
	TwAddVarRW(ToolGUI, "Animate Camera", TW_TYPE_BOOL8, &animate_camera, "help=''");
	TwAddVarRW(ToolGUI, "Look At Apple", TW_TYPE_BOOL8, &look_at_apple, "help=''");
	TwAddVarRW(ToolGUI, "3rd Person", TW_TYPE_BOOL8, &third_person, "help=''");
	TwAddVarRW(ToolGUI, "Camera X", TW_TYPE_FLOAT, &cameraPosition.x, "step=0.1");
	TwAddVarRW(ToolGUI, "Camera Y", TW_TYPE_FLOAT, &cameraPosition.y, "step=0.1");
	TwAddVarRW(ToolGUI, "Camera Z", TW_TYPE_FLOAT, &cameraPosition.z, "step=0.1");


	// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);             // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar
}
