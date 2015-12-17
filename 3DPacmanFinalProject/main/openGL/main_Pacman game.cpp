//
//  main_Pacman game.cpp
//  Marcus Naik, Michael Hoefer, Nigel Lee, Yuanfen Chen
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.

//loaded maze 12/5/2015
//modified GLObjectObj, loaded pacman 12/6/2015 
//created 40 small spheres, 12/6/2015 
//created GLDiamond, two purple diamond, 12/14/2015 
//Enviorenment mapping on pacman, displacement mapping on maze ground, texture.cpp modified to compatible with both kind of texure,12/15/2015 
//color combined light, tigger light on the big shpere on top, 12/16/2015 

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "SphereInt3D.h"
#include "GLDiamond.h"
#include "Plane3D.h"

#include "GLObjectObj.h"
#include "RayIntersectionTest.h"

// small ball location created by Yuanfen
float ball_locations[40][2] = { { -7.3,-7.3 },{ -7.3,-5.5 },{ -7.3,-3.5 },{ -7.3,-1.5 },{ -7.3,3.5 },{ -7.3,5.5 },{ -7.3,7.3 },//7
{ -5.5,-1.5 },{ -3.5,-1.5 },{ -1.5,-1.5 },//3
{ -5.5,1.5 },{ -3.5,1.5 },{ -1.5,1.5 },//3
{ -5.5,7.3 },{ -3.5,7.3 },{ -1.5,7.3 },{ 0.5,7.3 },{ 2.5,7.3 },{ 4.5,7.3 },{ 6.5,7.3 },//7
{ -3.0,4.5 },{ -0.8,4.5 },{ 1.5,4.5 },{ 4.5,4.5 },//4
{ -4.5,-4.5 },{ -2.0,-4.5 },{ 1.0,-4.5 },//3
{ -4.5,-7.4 },{ -1.0,-7.4 },{ 1.5,-7.4 },{ 4.0,-7.4 },//4
{ 1.5,1.8 },{ 4.5,-1.5 },{ 4.5,1.5 },//3
{ 7.3,6.2 },{ 7.3,4.2 },{ 7.3,2.0 },{ 7.3,-3.0 },{ 7.3,-5.5 },{ 7.3,-7.3 }//6

};
using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;


// The rorating big sphere 
GLSphere3D* sphere_blue;
glm::mat4 sphere_blue_transform;

// two purple diamonds 
GLDiamond * dia1;
glm::mat4 dia1_transform;
GLDiamond * dia2;
glm::mat4 dia2_transform;


// vector of spheres  
vector<GLSphereInt3D*> spheres;

// The sphere object
GLSphereInt3D* sphere_result;

// The loaded object
GLObjectObj* loadedModel1;
GLObjectObj* loadedModel2;

// pacman's appearance
GLAppearance* apperance_pacman;

//maze apperance
GLAppearance* apperance_0;

//the pacman transform
glm::mat4 pacman_tranform;
glm::mat4 pacman_temp_transform;

// to transform the sphere
glm::mat4 g_tranform_sphere;
glm::mat4 g_tranform_sphere_result;
glm::mat4 g_view_result;

// NEW added by Mike: ray intersection with pacman
//glm::mat4 g_tranform_pacman; //this is the pacman_transform
glm::mat4 g_tranform_pacman_result;

// to swap between navigation with interpolation and without interpolation.
int    g_with_interpolation = 1;


int    g_swap_trackball_navigation = 0;

float g_delta = 3;  //0.4

// this keeps track of the pacman rotations
// increment/decrement accordingly when the ASD keys are pressed, and change the ray intersection appropriately
int currentDirection = 0;

// these values are changed according to the currentDirection for the ray intersection text. 
float rayXdelta = .5;
float rayYdelta = 0;

int lightsource_flag=0;

 GLDirectLightSource  light_source_direct;
 GLAppearance* apperance_sphere_blue;

// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	bool move = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == 49 && action == GLFW_PRESS) // 1
	{
		g_with_interpolation++;
		g_with_interpolation = g_with_interpolation % 2;
		//can't focus now
		// sphere->enableInterpolation((bool)g_with_interpolation);
		// sphere_result->enableInterpolation((bool)g_with_interpolation);
		//loadedModel2->enableInterpolation((bool)g_with_interpolation);
	}
	else if (key == 50 && action == GLFW_PRESS) // 2
	{
		g_swap_trackball_navigation++;
		g_swap_trackball_navigation = g_swap_trackball_navigation % 2;
	}


	////////////////////////////////////////////////////////////////////////////////////////////
	// Translation
	if ((key == 87 && action == GLFW_REPEAT) || (key == 87 && action == GLFW_PRESS)) // key w
	{
		// if you keep going in circles, then the currentDirection will get too big.
		// this limits the options to 0, 90, 180, and 270
		currentDirection = currentDirection % 360;

		// ensures that currentDirection is always positive
		if (currentDirection < 0)
		{
			currentDirection = currentDirection + 360;
		}
		switch (currentDirection)
		{
		case 0:
			rayXdelta = 1;
			rayYdelta = 0;
			lightsource_flag=0;

			break;
		case 90:
			rayXdelta = 0;
			rayYdelta = 1;
			lightsource_flag=1;

			break;
		case 180:
			rayXdelta = -1;
			rayYdelta = 0;
			lightsource_flag=2;

			break;
		case 270:
			rayXdelta = 0;
			rayYdelta = -1;
			lightsource_flag=3;
			break;
		default:
			//this should never happen
			break;
		}


		cout << "rayX=" << rayXdelta << "rayY=" << rayYdelta << "currentDirection=" << currentDirection << endl;
		//g_tranform_sphere =  g_tranform_sphere * glm::translate(glm::vec3( -g_delta,0.0, 0.0f));
		pacman_temp_transform = pacman_tranform * glm::translate(glm::vec3(0.0, g_delta, 0.0f));

		//do the ray intersection test with the maze here. 
		// If the pacman moving forward would hit a wall, do not allow the movement!
		// need to get dynamic direction that pacman is facing using rayXdelta and rayYdelta
		glm::vec3 s(pacman_temp_transform[3][0], pacman_temp_transform[3][1], pacman_temp_transform[3][2]);
		glm::vec3 e(pacman_temp_transform[3][0] + rayXdelta, pacman_temp_transform[3][1] + rayYdelta, pacman_temp_transform[3][2]);

		vector<glm::vec3> mazeRes;

		// perform the ray intersectiont test. Check if moving forward hit the wall
		RayIntersectionTest::intersect(s, e, *loadedModel1, mazeRes);
		if (mazeRes.size() > 0) {
			// Mike newly added: ray intersection handling
			//if it reaches a wall, don't allow the movement.

			/*	glm::vec3 position = res[0];

			g_tranform_pacman_result = pacman_tranform;
			g_tranform_pacman_result[3][0] = position[0];
			g_tranform_pacman_result[3][1] = position[1];
			g_tranform_pacman_result[3][2] = position[2];
			loadedModel2->setMatrix(g_tranform_pacman_result);*/
		}
		else
		{
			pacman_tranform = pacman_temp_transform;
			loadedModel2->setMatrix(pacman_tranform);

			// changes how sensitive pacmans mouth is
			float delta = .5;
			//glm::mat4 deleted_location(1,0,10,0);
			// now we check if pacman ran into any balls
			for (int i = 0; i < spheres.size(); i++)
			{

				// TODO
				// need to check the ball locations from the object rather than the initial values. 
				if (pacman_tranform[3][0] < ball_locations[i][0] + delta && pacman_tranform[3][0] > ball_locations[i][0] - delta
					&& pacman_tranform[3][1] < ball_locations[i][1] + delta && pacman_tranform[3][1] > ball_locations[i][1] - delta)
				{
					// collision happened with object i
					glm::mat4 temp = glm::translate(glm::vec3(0.0f, 0.0f, 4.0f));
					spheres[i]->setMatrix(temp);
					//spheres.erase(spheres.begin() + i);
					cout << "collision with ball index " << i << "\n\n";

				}
				//RayIntersectionTest::intersect(s, e, (GLSphere3D)(spheres[i]), mazeRes);
			}

			// diamonds are a bit bigger than spheres
			delta = 1;
			// now check the first diamond  7.2, -0.5,
			if (pacman_tranform[3][0] < 7.2 + delta && pacman_tranform[3][0] > 7.2 - delta
				&& pacman_tranform[3][1] < -0.5 + delta && pacman_tranform[3][1] > -0.5 - delta)
			{
				if (dia1_transform[3][2] < 3)
				{
					dia1_transform = dia1_transform *  glm::translate(glm::vec3(0.0f, 0.0f, 4.0f));
					dia1->setMatrix(dia1_transform);
				}

				// make a new light source on pacman
				//GLDirectLightSource  light_source_pac; 
				//light_source_pac._lightPos = glm::vec4(20.0,20.0,0.0, 0.0);
				//light_source_pac._ambient_intensity = 0.2;
				//light_source_pac._specular_intensity = 0.5;
				//light_source_pac._diffuse_intensity = 2.0;
				//light_source_pac._attenuation_coeff = 0.0;
				//apperance_0->addLightSource(light_source_pac);
				//apperance_0->updateLightSources();
				

			}
			// now check the second diamond 1.6, -1.5,
			if (pacman_tranform[3][0] < 1.6 + delta && pacman_tranform[3][0] > 1.6 - delta
				&& pacman_tranform[3][1] < -1.5 + delta && pacman_tranform[3][1] > -1.5 - delta)
			{
				if (dia2_transform[3][2] < 3)
				{
					dia2_transform = dia2_transform *  glm::translate(glm::vec3(0.0f, 0.0f, 4.0f));
					dia2->setMatrix(dia2_transform);
				}
				// make a new light source on pacman
				//GLDirectLightSource  light_source_pac;
				//light_source_pac._lightPos = glm::vec4(0.0, 0.0, 0.0, 0.0);
				//light_source_pac._ambient_intensity = 0.2;
				//light_source_pac._specular_intensity = 0.5;
				//light_source_pac._diffuse_intensity = 200.0;
				//light_source_pac._attenuation_coeff = 0.0;
				//apperance_0->addLightSource(light_source_pac);
				//apperance_0->updateLightSources();
			}
		}






		// now only the forward button moves pacman, so no need for "move" variable
		//move = true;
	}
	else if ((key == 83 && action == GLFW_REPEAT) || (key == 83 && action == GLFW_PRESS)) // key s 
	{
		currentDirection += 180;
		// switch the functionality to 180 rotation
		//cout <<  "key s pressed" << endl;
		// Mike newly added: make pacman do a 180 flip instead of moving backwards
		pacman_tranform = pacman_tranform* glm::rotate(3.14f, glm::vec3(0.0f, 0.0f, 1.0f));// rotate 90 degee
		loadedModel2->setMatrix(pacman_tranform);
		//move = true;
		/*	pacman_tranform = pacman_tranform * glm::translate(glm::vec3(0.0, g_delta, 0.0f));
		loadedModel2->setMatrix(pacman_tranform);
		move = true;*/
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	// Rotation
	if ((key == 65 && action == GLFW_REPEAT) || (key == 65 && action == GLFW_PRESS)) // key a  /just press to turn 90 degree
	{
		currentDirection += 90;
		//cout <<  "key a pressed" << endl;
		// Mike newly added: make pacman do 90 degree complete rotation
		pacman_tranform = pacman_tranform* glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f));// rotate 90 degee

																						   //pacman_tranform = pacman_tranform* glm::rotate(0.04f, glm::vec3(0.0f, 0.0f, 1.0f));// rotate 90 degee
		loadedModel2->setMatrix(pacman_tranform);
		//move = true;
	}

	else if ((key == 68 && action == GLFW_REPEAT) || (key == 68 && action == GLFW_PRESS)) // key d
	{
		currentDirection -= 90;
		//cout <<  "key d pressed" << endl;
		// Mike newly added: make pacman do 90 degree complete rotation
		pacman_tranform = pacman_tranform* glm::rotate(-1.57f, glm::vec3(0.0f, 0.0f, 1.0f));// rotate 90 degee

																							//pacman_tranform = pacman_tranform * glm::rotate(-0.04f, glm::vec3(0.0f, 0.0f, 1.0f));
		loadedModel2->setMatrix(pacman_tranform);
		//move = true;
	}


	if (move)
	{
		glm::vec3 s(pacman_tranform[3][0], pacman_tranform[3][1], pacman_tranform[3][2]);
		glm::vec3 e(pacman_tranform[3][0] + 5, pacman_tranform[3][1], pacman_tranform[3][2]);
		vector<glm::vec3> res;

		// perform the ray intersectiont test.
		RayIntersectionTest::intersect(s, e, *loadedModel1, res);

		// pick the first result if one is available
		if (res.size() > 0) {
			// Mike newly added: ray intersection handling
			//if it reaches a wall, don't allow the movement.

			glm::vec3 position = res[0];

			g_tranform_pacman_result = pacman_tranform;
			g_tranform_pacman_result[3][0] = position[0];
			g_tranform_pacman_result[3][1] = position[1];
			g_tranform_pacman_result[3][2] = position[2];
			loadedModel2->setMatrix(g_tranform_pacman_result);
		}


	}

	//cout << key << endl;
}



int main(int argc, const char * argv[])
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Init glfw, create a window, and init glew

	// Init the GLFW Window
	window = initWindow();


	// Init the glew api
	initGlew();
	SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);// focus model, on the yellow ball



 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Create the maze cteated by Yuanfen 

// coordinate system
	CoordSystem* cs = new CoordSystem(40.0);


	// create an apperance object.
	apperance_0 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

	GLDirectLightSource  light_source_direct;
	light_source_direct._lightPos = glm::vec4(0.0, 0.0, 20.0, 0.0);
	light_source_direct._ambient_intensity = 0.5;
	light_source_direct._specular_intensity = 1.0;
	light_source_direct._diffuse_intensity = 0.5;
	light_source_direct._attenuation_coeff = 0.01;

	// add the light to this apperance object
	apperance_0->addLightSource(light_source_direct);//add on the big shpere 
    


  // apperance_0->addLightSource(light_source_spot);

	// Create a material object
	GLMaterial material_0;
	material_0._diffuse_material = glm::vec3(0.2, 1.0, 0.2);
	material_0._ambient_material = glm::vec3(0.5, 0.5, 0.5);
	material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_0._shininess = 2.0;
	material_0._transparency = 1.0;

	// Add the material to the apperance object
	apperance_0->setMaterial(material_0);
	apperance_0->finalize();

	// If you want to change appearance parameters after you init the object, call the update function
	apperance_0->updateLightSources();


	loadedModel1 = new GLObjectObj("../data/objective/maze2.5.obj");
	loadedModel1->setApperance(*apperance_0);
	loadedModel1->init();

	// This scales the underground model
	glm::mat4 tranform1 = glm::scale(glm::vec3(3.0f, 3.0f, 3.0f));
	glm::mat4 rotate_mat1 = glm::rotate(1.570796f, glm::vec3(1.0f, 0.0f, 0.0f));//rotation
																				//glm::mat4 transform_mat1 = glm::translate(glm::vec3(5.0f,0.0f, 0.0f));//translate in x 

	//tranform1 = transform_mat1 * rotate_mat1 * tranform1;
	tranform1 = rotate_mat1 * tranform1;

	loadedModel1->setMatrix(tranform1);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// Create the pacman model cteated by Yuanfen

	//// create an apperance object.
	apperance_pacman = new GLAppearance("../../data/shaders/spherical_mapping.vs", "../../data/shaders/spherical_mapping.fs"); //enviroment mapping, use texture unit 0, texure cpp modified
	//("../data/shaders/multi_vertex_lights.vs", "../data/shaders/multi_vertex_lights.fs");

	// add the light to this apperance object
	apperance_pacman->addLightSource(light_source_direct);

	// Create a material object
	GLMaterial material_pacman;
	material_pacman._diffuse_material = glm::vec3(0.5, 0.5, 0.5);
	material_pacman._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	material_pacman._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_pacman._shininess = 2.0;
	material_pacman._transparency = 1.0;

	// Add the material to the apperance object
	apperance_pacman->setMaterial(material_pacman);

	//************************************************************************************************
	// Add a texture
	GLTexture* texture = new GLTexture();
	texture->loadAndCreateTexture("../../data/textures/reflactance_map1.bmp");
	apperance_0->setTexture(texture);

	//finalize the appearance
	apperance_pacman->finalize();


	// If you want to change appearance parameters after you init the object, call the update function
	apperance_pacman->updateLightSources();


	loadedModel2 = new GLObjectObj("../data/objective/Pacmansmall2.obj");
	loadedModel2->setApperance(*apperance_pacman);
	loadedModel2->init();

	// This scales the pacman model
	glm::mat4 tranform2 = glm::scale(glm::vec3(0.10f, 0.10f, 0.10f));
	//glm::mat4 rotate_mat2 = glm::rotate(-1.570796f, glm::vec3(0.0f, 0.0f, 1.0f));//rotation
	glm::mat4 rotate_mat2 = glm::rotate(4.71f, glm::vec3(0.0f, 0.0f, 1.0f));//rotation
	glm::mat4 transform_mat2 = glm::translate(glm::vec3(-10.0f, -1.5f, 2.0f));//translate in x,y,z

																			  //tranform2 = transform_mat2 * rotate_mat2 * tranform2;
																			  //pacman_tranform = transform_mat2 * tranform2;
	pacman_tranform = transform_mat2 * rotate_mat2 * tranform2;

	loadedModel2->setMatrix(pacman_tranform);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create the plane cteated by Yuanfen
	// create an apperance object.
	GLAppearance* apperance_plane = new GLAppearance("../../data/shaders/noisemap.vs", "../../data/shaders/noisemap.fs");
		//("../../data/shaders/multi_texture.vs", "../../data/shaders/multi_texture.fs");
		//("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

	// add the light to this apperance object
	apperance_plane->addLightSource(light_source_direct);

	// Create a material object
	GLMaterial material_plane;
	material_plane._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
	material_plane._ambient_material = glm::vec3(1.0, 0.2, 0.2);
	material_plane._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_plane._shininess = 2.0;
	material_plane._transparency = 1.0;

	// Add the material to the apperance object
	apperance_plane->setMaterial(material_plane);
  
    //************************************************************************************************
    // Add a texture
    GLMultiTexture* texture_maze = new GLMultiTexture();
    int texid_maze = texture_maze->loadAndCreateTextures("../../data/textures/gradient.bmp", "../../data/textures/tiles.bmp");//use texture unit 1,2 texture.cpp modified

    apperance_plane->setTexture(texture_maze);

	//finalize the apperance
	apperance_plane->finalize();


	// If you want to change appearance parameters after you init the object, call the update function
	apperance_plane->updateLightSources();

    GLPlane3D* plane = new GLPlane3D(0.0, 0.0, 1.0, 18.0, 18.0);
    plane->setApperance(*apperance_plane);
    plane->init();


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create the 20 red sphere cteated by Yuanfen

	GLAppearance* apperance_sphere_red = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	// add the light to this apperance object
	apperance_sphere_red->addLightSource(light_source_direct);


	// Create a material object
	GLMaterial material_sphere;
	material_sphere._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
	material_sphere._ambient_material = glm::vec3(1.0, 0.0, 0.0);
	material_sphere._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_sphere._shininess = 2.0;
	material_sphere._transparency = 1.0;

	// Add the material to the apperance object
	apperance_sphere_red->setMaterial(material_sphere);
	apperance_sphere_red->finalize();


	//g_tranform_sphere = glm::translate(glm::vec3(0.0, 0.0f, 2.0f));
	for (int i = 0; i < 20; i++)
	{
		spheres.push_back(new GLSphereInt3D(ball_locations[i][0], ball_locations[i][1], 2.0, 0.5));
		spheres[i]->setApperance(*apperance_sphere_red);
		spheres[i]->init();
		//spheres[i].setMatrix(g_tranform_sphere);
	}
	// Create a sphere
	//  sphere = new GLSphereInt3D(0.0, 0.0, 0.0, 0.5);
	//  sphere->setApperance(*apperance_sphere_red);
	// sphere->init();

	// move the sphere up
	// g_tranform_sphere = glm::translate(glm::vec3(0.0, 0.0f, 2.0f));
	//sphere->setMatrix(g_tranform_sphere);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create 20 yellow sphere cteated by Yuanfen

	GLAppearance* apperance_sphere_yellow = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	// add the light to this apperance object
	apperance_sphere_yellow->addLightSource(light_source_direct);


	// Create a material object
	GLMaterial material_sphere2;
	material_sphere2._diffuse_material = glm::vec3(1.0, 1.0, 0.0);
	material_sphere2._ambient_material = glm::vec3(1.0, 1.0, 0.0);
	material_sphere2._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_sphere2._shininess = 2.0;
	material_sphere2._transparency = 1.0;

	// Add the material to the apperance object
	apperance_sphere_yellow->setMaterial(material_sphere2);
	apperance_sphere_yellow->finalize();

	//GLSphereInt3D spheres[20];
	//g_tranform_sphere_result = glm::translate(glm::vec3(0.0, 0.0f, 2.0f));

	for (int i = 20; i < 40; i++)
	{
		spheres.push_back(new GLSphereInt3D(ball_locations[i][0], ball_locations[i][1], 2.0, 0.5));
		spheres[i]->setApperance(*apperance_sphere_yellow);
		spheres[i]->init();
		//spheres[i].setMatrix(g_tranform_sphere_result);
	}
	/* sphere_result = new GLSphereInt3D(0.0, 0.0, 0.0, 0.5);

	sphere_result->setApperance(*apperance_sphere2);
	sphere_result->init();*/


	/*g_tranform_sphere_result = glm::translate(glm::vec3(0.0, 0.0f, 5.0f));*/
	/*sphere_result->setMatrix(g_tranform_sphere_result);*/
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// draw diamond 1 Created by Yuanfen
	GLAppearance* apperance_diamond1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	// add the light to diamond apperance object
	apperance_diamond1->addLightSource(light_source_direct);


	// Create a material object
	GLMaterial material_diamond;
	material_diamond._diffuse_material = glm::vec3(1.0, 0.0, 1.0);
	material_diamond._ambient_material = glm::vec3(1.0, 0.0, 1.0);
	material_diamond._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_diamond._shininess = 2.0;
	material_diamond._transparency = 1.0;

	// Add the material to the apperance object
	apperance_diamond1->setMaterial(material_diamond);
	apperance_diamond1->finalize();

	dia1 = new GLDiamond(0.0, 0.0, 0.0, 1);// position and scale
	
	dia1_transform = glm::translate(glm::vec3(7.2f, -0.5f, 2.0f));//(0.0f, 0.0f,3.5f)
	dia1->setMatrix(dia1_transform);
	dia1->setApperance(*apperance_diamond1);
	dia1->init();


	///////////////////////////////////////////////////////////////////////////////////////////
	// draw diamond 2 Created by Yuanfen
	GLAppearance* apperance_diamond2 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	// add the light to diamond apperance object
	apperance_diamond2->addLightSource(light_source_direct);

	// Add the material to the apperance object
	apperance_diamond2->setMaterial(material_diamond);
	apperance_diamond2->finalize();

	dia2 = new GLDiamond(0, 0, 0, 1);// position and scale
	dia2_transform = glm::translate(glm::vec3(1.6f, -1.5f, 2.0f));
	dia2->setMatrix(dia2_transform);
	dia2->setApperance(*apperance_diamond2);
	dia2->init();


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create blue sphere Created by Yuanfen

	apperance_sphere_blue = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	// add the light to this apperance object

		//creat spot light 
    GLSpotLightSource  light_source_spot;

    light_source_spot._lightPos = glm::vec4(0.0,0.0,10.0, 1.0);//the spot light will be shaded from the +z;Yuanfen
    light_source_spot._ambient_intensity = 0.4;
    light_source_spot._specular_intensity = 2.0;
    light_source_spot._diffuse_intensity = 1.5;
    light_source_spot._attenuation_coeff = 0.01;
    light_source_spot._cone_angle = 10.0; // in degree
    light_source_spot._cone_direction = glm::vec3(0.0, 0.0, -1.0);

	apperance_sphere_blue->addLightSource(light_source_spot);

	//create direct light for sphere_blue
	GLDirectLightSource  light_source_direct1;
	light_source_direct1._lightPos = glm::vec4(20.0, 0.0, 0.0, 0.0);
	light_source_direct1._ambient_intensity = 0.5;
	light_source_direct1._specular_intensity = 1.0;
	light_source_direct1._diffuse_intensity = 0.5;
	light_source_direct1._attenuation_coeff = 0.01;

	apperance_sphere_blue->addLightSource(light_source_direct1);

	// Create a material object
	GLMaterial material_sphere_blue;
	material_sphere_blue._diffuse_material = glm::vec3(1.0, 0.0, 0.0); //red 
	material_sphere_blue._ambient_material = glm::vec3(0.0, 0.0, 1.0); //blue
	material_sphere_blue._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_sphere_blue._shininess = 15.0;
	material_sphere_blue._transparency = 1.5;


	// Add the material to the apperance object
	apperance_sphere_blue->setMaterial(material_sphere_blue);
	apperance_sphere_blue->finalize();

	apperance_sphere_blue->updateLightSources();

	sphere_blue = new GLSphere3D(0.0, 0.0, 0.0, 1.5f, 50, 50); //GLSphereInt3D(0.0f, 0.0f, 0.0f, 1.5f);
	sphere_blue->setApperance(*apperance_sphere_blue);
	sphere_blue->init();

	sphere_blue_transform = glm::translate(glm::vec3(0.0f, 0.0f, 5.0f));
	sphere_blue->setMatrix(sphere_blue_transform);
	
	


	/*g_tranform_sphere_result = glm::translate(glm::vec3(0.0, 0.0f, 5.0f));*/
	/*sphere_result->setMatrix(g_tranform_sphere_result);*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Main render loop

	// Set up our green background color
	static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// This sets the camera to a new location
	// the first parameter is the eye position, the second the center location, and the third the up vector. 
	SetViewAsLookAt(glm::vec3(12.0f, 65.0f, 12.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	// Enable depth test
	// ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
	glEnable(GL_DEPTH_TEST);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Blending

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Here we set a new keyboard callback

	// Set the keyboard callback so that when we press ESC, it knows what to do.
	glfwSetKeyCallback(window, keyboard_callback);


	glm::mat4 camera_transformation = glm::lookAt(glm::vec3(-5.5f, -30.0f, 30.5f), glm::vec3(-10.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 object_transformation = glm::mat4();
	glm::mat4 camera_matrix = glm::mat4();
	glm::mat4 camera_delta = glm::rotate(-0.4f, glm::vec3(1.0f, 0.0f, 0.0f));



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Main render loop

	// This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
	while (!glfwWindowShouldClose(window))
	{

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//triggered light. The direct light shade the same direction as the pacman move. Created by Yuanfen

		switch (lightsource_flag)
		{case 0:
			light_source_direct1._lightPos = glm::vec4(20.0, 0.0, 0.0, 0.0);
			light_source_direct1._ambient_intensity = 0.3;
			light_source_direct1._specular_intensity = 0.5;
			light_source_direct1._diffuse_intensity = 2.0;
			light_source_direct1._attenuation_coeff = 0.002;

			apperance_sphere_blue->updateLightSources();
			break;
		case 1:
			light_source_direct1._lightPos = glm::vec4(0.0, 20.0, 0.0, 0.0);
			light_source_direct1._ambient_intensity = 0.3;
			light_source_direct1._specular_intensity = 0.5;
			light_source_direct1._diffuse_intensity = 2.0;
			light_source_direct1._attenuation_coeff = 0.002;

			apperance_sphere_blue->updateLightSources();
			break;
		case 2:
			light_source_direct1._lightPos = glm::vec4(-20.0, 0.0, 0.0, 0.0);
			light_source_direct1._ambient_intensity = 0.3;
			light_source_direct1._specular_intensity = 0.5;
			light_source_direct1._diffuse_intensity = 2.0;
			light_source_direct1._attenuation_coeff = 0.002;

			apperance_sphere_blue->updateLightSources();
			break;
		case 3:
			light_source_direct1._lightPos = glm::vec4(0.0, -20.0, 0.0, 0.0);
			light_source_direct1._ambient_intensity = 0.3;
			light_source_direct1._specular_intensity = 0.5;
			light_source_direct1._diffuse_intensity = 2.0;
			light_source_direct1._attenuation_coeff = 0.002;
			apperance_sphere_blue->updateLightSources();
			break;
		default:
			//this should never happen
			break;
		}
		//// This renders the objects

		// draw the objects
		cs->draw();

		loadedModel1->draw();
		loadedModel2->draw();
		plane->draw();

		 //rotate the diamonds a bit here
		dia1_transform = dia1_transform * glm::rotate(6.28f, glm::vec3(0.0f, 0.0f, 1.0f));
		dia1->setMatrix(dia1_transform);

		dia2_transform = dia2_transform * glm::rotate(.001f, glm::vec3(0.0f, 0.0f, 1.0f));
		dia2->setMatrix(dia2_transform);

		dia1->draw();
		dia2->draw();
		sphere_blue->draw();
		//  sphere->draw();
		for (int i = 0; i < 40; i++)
		{
			spheres[i]->draw();
		}

		// Camera manipulation
		if (g_swap_trackball_navigation == 0)
		{
			// This code attaches the virtual camera just behind the object.
			// Read the location from the object on the ground

			//object_transformation = sphere_result->getModelMatrix();
			object_transformation = loadedModel2->getModelMatrix();//change spheres[0] to pacman

																   // Add the camera and a camera delta
			camera_matrix = camera_delta *  camera_transformation * glm::inverse(object_transformation);

			// set the view matrix
			SetViewAsMatrix(camera_matrix);

	//light_source_direct._lightPos = glm::vec4(0.0, 0.0, 20.0, 0.0);
	//light_source_direct._ambient_intensity = 0.5;
	//light_source_direct._specular_intensity = 1.0;
	//light_source_direct._diffuse_intensity = 0.5;
	//light_source_direct._attenuation_coeff = 0.01;
	//
	//apperance_sphere_blue->updateLightSources();

		}
		else
		{
			// Set the trackball locatiom
			SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());


	//light_source_direct._lightPos = glm::vec4(0.0, 20.0, 0.0, 0.0);
	//light_source_direct._ambient_intensity = 0.3;
	//light_source_direct._specular_intensity = 0.5;
	//light_source_direct._diffuse_intensity = 2.0;
	//light_source_direct._attenuation_coeff = 0.002;

	//		apperance_sphere_blue->updateLightSources();
		}


		//// This renders the objects
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	delete cs;


}

