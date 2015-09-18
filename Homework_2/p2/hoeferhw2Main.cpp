//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"


using namespace std;

static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];
unsigned int vboID[4];


/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[0] for this model representation
    
    
    //TODO:

	float* vertices = new float[100];
	float *colors = new float[100];
	// Back tall face
	vertices[0] = 0.0; vertices[1] = 0.0; vertices[2] = 0.0; // origin
	colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // Top left corner

	vertices[3] = 0.0; vertices[4] = 2.0; vertices[5] = 0.0; // far back corner
	colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // Bottom left corner

	vertices[6] = 0.0; vertices[7] = 0.0; vertices[8] = 1.0; // Top Right corner
	colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // Top Right corner

	vertices[9] = 0.0; vertices[10] = 2.0; vertices[11] = 1.0; // Bottom right corner
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner
	// end back tall face
	
	// Rectangular piece vertical sides
	vertices[12] = 0.0; vertices[13] = 0.0; vertices[14] = 1.0; // Top right corner
	colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0; // Top right corner

	vertices[15] = 0.0; vertices[16] = 1.0; vertices[17] = 1.0; // Bottom right corner
	colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // Bottom right corner

	vertices[18] = 0.0; vertices[19] = 0.0; vertices[20] = 3.0; // Top left  corner
	colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0; // Top left corner

	vertices[21] = 0.0; vertices[22] = 1.0; vertices[23] = 3.0; // Bottom left  corner
	colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0; // Bottom left corner

	vertices[24] = 1.0; vertices[25] = 0.0; vertices[26] = 3.0; // Top left  corner
	colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0; // Top left corner

	vertices[27] = 1.0; vertices[28] = 1.0; vertices[29] = 3.0; // Bottom left  corner
	colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0; // Bottom left corner

	vertices[30] = 1.0; vertices[31] = 0.0; vertices[32] = 1.0; // Top left  corner
	colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0; // Top left corner

	vertices[33] = 1.0; vertices[34] = 1.0; vertices[35] = 1.0; // Bottom left  corner
	colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0; // Bottom left corner
	//end rectangular piece vertical sides

														  //TOP
	vertices[36] = 3.0; vertices[37] = 0.0; vertices[38] = 1.0; // Top left  corner
	colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0; // Top left corner

	vertices[39] = 3.0; vertices[40] = 1.0; vertices[41] = 1.0; // Bottom left  corner
	colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0; // Bottom left corner

	vertices[42] = 3.0; vertices[43] = 0.0; vertices[44] = 0.0; // Top left  corner
	colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0; // Top left corner

	vertices[45] = 3.0; vertices[46] = 1.0; vertices[47] = 0.0; // Bottom left  corner
	colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0; // Bottom left corner

	vertices[48] = 0.0; vertices[49] = 0.0; vertices[50] = 0.0; // Bottom left  corner
	colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0; // Bottom left corner

	vertices[51] = 1.0; vertices[52] = 2.0; vertices[53] = 0.0; // Bottom left  corner
	colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0; // Bottom left corner

	vertices[54] = 0.0; vertices[55] = 2.0; vertices[56] = 0.0; // Bottom left  corner
	colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0; // Bottom left corner

	//new triangle fan
	vertices[57] = 0.0; vertices[58] = 2.0; vertices[59] = 0.0; // Top left  corner
	colors[57] = 0.0; colors[58] = 0.8; colors[59] = 0.5; // Top left corner

	vertices[60] = 1.0; vertices[61] = 2.0; vertices[62] = 0.0; // Top left  corner
	colors[60] = 0.3; colors[61] = 0.8; colors[62] = 0.2; // Top left corner

	vertices[63] = 0.0; vertices[64] = 2.0; vertices[65] = 1.0; // Top left  corner
	colors[63] = 0.1; colors[64] = 0.8; colors[65] = 0.7; // Top left corner

	vertices[66] = 1.0; vertices[67] = 2.0; vertices[68] = 1.0; // Top left  corner
	colors[66] = 0.7; colors[67] = 0.8; colors[68] = 0.0; // Top left corner

	vertices[69] = 0.0; vertices[70] = 1.0; vertices[71] = 1.0; // Top left  corner
	colors[69] = 0.5; colors[70] = 0.8; colors[71] = 0.7; // Top left corner

	vertices[72] = 1.0; vertices[73] = 1.0; vertices[74] = 1.0; // Top left  corner
	colors[72] = 0.0; colors[73] = 0.8; colors[74] = 0.0; // Top left corner

	//end
	vertices[75] = 3.0; vertices[76] = 1.0; vertices[77] = 1.0; // Top left  corner
	colors[54] = 0.0; colors[76] = 0.4; colors[77] = 0.0; // Top left corner

	vertices[78] = 1.0; vertices[79] = 2.0; vertices[80] = 1.0; // Top left  corner
	colors[78] = 0.0; colors[79] = 0.2; colors[80] = 0.1; // Top left corner

	vertices[81] = 0.0; vertices[82] = 2.0; vertices[83] = 1.0; // Top left  corner
	colors[81] = 0.4; colors[82] = 0.9; colors[83] = 0.9; // Top left corner

	
	glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
	//unsigned int vboID[2]; // Our Vertex Buffer Object
	glGenBuffers(2, &vboID[0]); // Generate our Vertex Buffer Object



	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


								  //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array



	glBindVertexArray(0); // Disable our Vertex Buffer Object

	delete[] vertices; // Delete our vertices from memory
	

    return 1;
}

/*!
ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
*/
void renderTriangleStripModel(void)
{
	glBindVertexArray(vaoID[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 15);
	glDrawArrays(GL_TRIANGLE_STRIP, 19, 6);
	glBindVertexArray(0);



}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createMyModel(void)
{

	float* vertices = new float[234];
	float *colors = new float[234];
	//first triangle
	vertices[0] = 0.0; vertices[1] = 0.0; vertices[2] = 0.0; // Top left corner
	colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0; // Top left corner

	vertices[3] = 0.0; vertices[4] = 2.0; vertices[5] = 0.0; // Bottom left corner
	colors[3] = 1.0; colors[4] = 1.0; colors[5] = 1.0; // Bottom left corner

	vertices[6] = 0.0; vertices[7] = 0.0; vertices[8] = 1.0; // Top Right corner
	colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // Top Right corner
	//end first triangle

	//second tri
	vertices[9] = 0.0; vertices[10] = 0.0; vertices[11] = 1.0; // Bottom right corner
	colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner
										 
	vertices[12] = 0.0; vertices[13] = 2.0; vertices[14] = 1.0; // Top right corner
	colors[12] = 1.0; colors[13] = 1.0; colors[14] = 0.0; // Top right corner

	vertices[15] = 0.0; vertices[16] = 2.0; vertices[17] = 0.0; // Bottom right corner
	colors[15] = 1.0; colors[16] = 0.0; colors[17] = 1.0; // Bottom right corner
	// end second tri

	// third triangle
	vertices[18] = 0.0; vertices[19] = 0.0; vertices[20] = 1.0; // Top left  corner
	colors[18] = 0.0; colors[19] = 0.5; colors[20] = 0.5; // Top left corner

	vertices[21] = 0.0; vertices[22] = 1.0; vertices[23] = 1.0; // Bottom left  corner
	colors[21] = 0.5; colors[22] = 0.5; colors[23] = 0.0; // Bottom left corner
										
	vertices[24] = 0.0; vertices[25] = 0.0; vertices[26] = 3.0; // Top left  corner
	colors[24] = 1.0; colors[25] = 0.0; colors[26] = 0.0; // Top left corner
	// end third tri

	//fourth tri
	vertices[27] = 0.0; vertices[28] = 1.0; vertices[29] = 1.0; // Bottom left  corner
	colors[27] = 0.5; colors[28] = 0.5; colors[29] = 0.0; // Bottom left corner

	vertices[30] = 0.0; vertices[31] = 0.0; vertices[32] = 3.0; // Top left  corner
	colors[30] = 1.0; colors[31] = 0.0; colors[32] = 0.0; // Top left corner

	vertices[33] = 0.0; vertices[34] = 1.0; vertices[35] = 3.0; // Bottom left  corner
	colors[33] = 1.0; colors[34] = 1.0; colors[35] = 0.0; // Bottom left corner
	//end fourth tri
	

	//fifth triangle
	vertices[36] = 0.0; vertices[37] = 0.0; vertices[38] = 3.0; // Top left  corner
	colors[36] = 0.0; colors[37] = 1.0; colors[38] = 0.0; // Top left corner

	vertices[39] = 0.0; vertices[40] = 1.0; vertices[41] = 3.0; // Bottom left  corner
	colors[39] = 0.0; colors[40] = 0.3; colors[41] = 0.0; // Bottom left corner

	vertices[42] = 1.0; vertices[43] = 1.0; vertices[44] = 3.0; // Top left  corner
	colors[42] = 0.0; colors[43] = 0.8; colors[44] = 0.0; // Top left corner

	//6th
	vertices[45] = 0.0; vertices[46] = 0.0; vertices[47] = 3.0; // Top left  corner
	colors[45] = 0.0; colors[46] = 0.8; colors[47] = 0.0; // Top left corner

	vertices[48] = 1.0; vertices[49] = 1.0; vertices[50] = 3.0; // Top left  corner
	colors[48] = 0.0; colors[49] = 0.8; colors[50] = 0.0; // Top left corner

	vertices[51] = 1.0; vertices[52] = 0.0; vertices[53] = 3.0; // Top left  corner
	colors[51] = 0.0; colors[52] = 0.8; colors[53] = 0.0; // Top left corner
	
	//let's try a triangle fan
	vertices[54] = 1.0; vertices[55] = 1.0; vertices[56] = 1.0; // Top left  corner
	colors[54] = 0.0; colors[55] = 0.8; colors[56] = 0.0; // Top left corner

	vertices[57] = 0.0; vertices[58] = 1.0; vertices[59] = 1.0; // Top left  corner
	colors[57] = 0.0; colors[58] = 0.8; colors[59] = 0.5; // Top left corner

	vertices[60] = 0.0; vertices[61] = 1.0; vertices[62] = 3.0; // Top left  corner
	colors[60] = 0.3; colors[61] = 0.8; colors[62] = 0.2; // Top left corner

	vertices[63] = 1.0; vertices[64] = 1.0; vertices[65] = 3.0; // Top left  corner
	colors[63] = 0.1; colors[64] = 0.8; colors[65] = 0.7; // Top left corner

	vertices[66] = 1.0; vertices[67] = 0.0; vertices[68] = 3.0; // Top left  corner
	colors[66] = 0.7; colors[67] = 0.8; colors[68] = 0.0; // Top left corner

	vertices[69] = 1.0; vertices[70] = 0.0; vertices[71] = 1.0; // Top left  corner
	colors[69] = 0.5; colors[70] = 0.8; colors[71] = 0.7; // Top left corner

	vertices[72] = 3.0; vertices[73] = 0.0; vertices[74] = 1.0; // Top left  corner
	colors[72] = 0.0; colors[73] = 0.8; colors[74] = 0.0; // Top left corner

	vertices[75] = 3.0; vertices[76] = 1.0; vertices[77] = 1.0; // Top left  corner
	colors[54] = 0.0; colors[76] = 0.4; colors[77] = 0.0; // Top left corner

	vertices[78] = 1.0; vertices[79] = 2.0; vertices[80] = 1.0; // Top left  corner
	colors[78] = 0.0; colors[79] = 0.2; colors[80] = 0.1; // Top left corner

	vertices[81] = 0.0; vertices[82] = 2.0; vertices[83] = 1.0; // Top left  corner
	colors[81] = 0.4; colors[82] = 0.9; colors[83] = 0.9; // Top left corner
	//end triangle fan

	//triangle fans worked well, another one for the top
	vertices[84] = 1.0; vertices[85] = 2.0; vertices[86] = 0.0; // Top left  corner
	colors[84] = 0.0; colors[85] = 0.8; colors[86] = 0.0; // Top left corner

	vertices[87] = 0.0; vertices[88] = 2.0; vertices[89] = 0.0; // Top left  corner
	colors[87] = 0.0; colors[88] = 0.8; colors[89] = 0.0; // Top left corner

	vertices[90] = 0.0; vertices[91] = 2.0; vertices[92] = 1.0; // Top left  corner
	colors[90] = 0.0; colors[91] = 0.8; colors[92] = 0.0; // Top left corner

	vertices[93] = 1.0; vertices[94] = 2.0; vertices[95] = 1.0; // Top left  corner
	colors[93] = 0.0; colors[94] = 0.8; colors[95] = 0.0; // Top left corner

	vertices[96] = 3.0; vertices[97] = 1.0; vertices[98] = 1.0; // Top left  corner
	colors[96] = 0.0; colors[97] = 0.8; colors[98] = 0.0; // Top left corner

	vertices[99] = 3.0; vertices[100] = 1.0; vertices[101] = 0.0; // Top left  corner
	colors[99] = 0.0; colors[100] = 0.8; colors[101] = 0.0; // Top left corner

	vertices[102] = 3.0; vertices[102] = 0.0; vertices[103] = 0.0; // Top left  corner
	colors[102] = 0.0; colors[102] = 0.8; colors[103] = 0.0; // Top left corner

	vertices[104] = 1.0; vertices[105] = 0.0; vertices[106] = 0.0; // Top left  corner
	colors[104] = 0.0; colors[105] = 0.8; colors[106] = 0.0; // Top left corner

	vertices[107] = 0.0; vertices[108] = 0.0; vertices[109] = 0.0; // Top left  corner
	colors[107] = 0.0; colors[108] = 0.8; colors[109] = 0.0; // Top left corner

	// For some reason our last facet on each triangle fan isn't showing up
	// so we'll patch it with another triangle 
	vertices[110] = 1.0; vertices[111] = 2.0; vertices[112] = 0.0; // Top left  corner
	colors[110] = 0.0; colors[111] = 1.0; colors[112] = 1.0; // Top left corner

	vertices[113] = 0.0; vertices[114] = 2.0; vertices[115] = 0.0; // Top left  corner
	colors[113] = 0.0; colors[114] = 1.0; colors[115] = 1.0; // Top left corner
	
	vertices[116] = 0.0; vertices[117] = 0.0; vertices[118] = 0.0; // Top left  corner
	colors[116] = 0.0; colors[117] = 1.0; colors[118] = 1.0; // Top left corner


	glGenVertexArrays(1, &vaoID[1]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it
	//unsigned int vboID[2]; // Our Vertex Buffer Object
	glGenBuffers(2, &vboID[2]); // Generate our Vertex Buffer Object



	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 234 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


								  //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[3]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 234 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW



	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array



	glBindVertexArray(0); // Disable our Vertex Buffer Object
	delete[] vertices; // Delete our vertices from memory
    return 1;
}





/*!
 ADD YOUR CODE TO RENDER YOUR MODEL TO THIS FUNCTION
 */
void renderMyModel(void)
{
	glBindVertexArray(vaoID[1]);
	glDrawArrays(GL_TRIANGLES, 0, 18);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 10);
	glDrawArrays(GL_TRIANGLE_FAN, 28, 9);
	//glDrawArrays(GL_TRIANGLES, 37, 3);
	glBindVertexArray(0);

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    createMyModel();
    
}


/*!
 This function updates the virtual camera
 */
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix =  getViewMatrix(); // get the current view matrix
    
    return true;
}





int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    
    //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    // this creates the scene
    setupScene();
    
    

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        
        // update the virtual camera
        // ignore this line since we did not introduced cameras.
        updateCamera();
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader
        
        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderTriangleStripModel();
        
        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -1.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderMyModel();
        
        
        glUseProgram(0);
        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

