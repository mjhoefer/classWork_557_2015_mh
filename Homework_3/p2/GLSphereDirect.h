//
//  GLSphereExt.hpp
//  HCI557_Spotlight
//
//  Created by Rafael Radkowski on 9/26/15.
//  Changes made for class
//	ME 557
//	10 / 8 / 2015
//	By: Michael Hoefer, Anupu Prudhivi, and Hsin Miao Lee
//
#pragma once


// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"





class GLSphereDirect : public GLSphere
{
public:
    
    GLSphereDirect(float center_x, float center_y, float center_z, float radius, int rows = 10, 
		int segments = 10, glm::vec3 matl_ambient_color = glm::vec3(0.0, 0.5, 0.0), int lightSourceOption = 1);
    ~GLSphereDirect();
    

protected:
    
    
    
    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);


    
    // The spotlight object
    GLLightSource           _light_source1;
	

	//selects which light to use
	int _lightSourceOption;




};