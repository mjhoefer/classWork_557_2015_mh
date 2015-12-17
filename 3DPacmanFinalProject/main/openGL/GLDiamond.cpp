

//Created by Yuanfen 12/11/2015
//#include "StdAfx.h"
#include "GLDiamond.h"

static const string vs_string_GLDia_410 =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrixBox;                                    \n"
"uniform mat4 viewMatrixBox;                                           \n"
"uniform mat4 inverseViewMatrix;                                        \n"
"uniform mat4 modelMatrixBox;                                          \n"
"uniform vec3 diffuse_color;                                          \n"
"uniform vec3 ambient_color;                                          \n"
"uniform vec3 specular_color;                                          \n"
"uniform vec4 light_position;                                          \n"
"uniform float diffuse_intensity;                                          \n"
"uniform float ambient_intensity;                                          \n"
"uniform float specular_intensity;                                          \n"
"uniform float shininess;                                          \n"
"in vec3 in_Position;                                               \n"
"in vec3 in_Normal;                                                  \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"                                                                 \n"
"                                                                 \n"
"                                                                 \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    vec3 normal = normalize(in_Normal);                                                                        \n"
"    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));             \n"
"    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);                             \n"
"                                                                                                               \n"
"    vec4 surface_to_light =   normalize( light_position -  surfacePostion );                         \n"
"                                                                                                               \n"
"    // Diffuse color                                                                                           \n"
"    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                           \n"
"    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;                         \n"
"                                                                                                               \n"
"    // Ambient color                                                                                           \n"
"    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;                                          \n"
"                                                                                                               \n"
"    // Specular color                                                                                          \n"
"    vec3 incidenceVector = -surface_to_light.xyz;                                                              \n"
"    vec3 reflectionVector = reflect(incidenceVector, normal);                                   \n"
"    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);             \n"
"    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                     \n"
"    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                        \n"
"    float specular_coefficient = pow(cosAngle, shininess);                                                     \n"
"    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;                      \n"
"                                                                                                               \n"
"    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);               \n"
"                                                                                                               \n"
"    pass_Color = vec3(out_diffuse_color + out_ambient_color + out_specular_color);                             \n"
"}                                                                                                              \n";



static const string vs_string_GLDia_300 =
"#version 310 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrixBox;                                    \n"
"uniform mat4 viewMatrixBox;                                           \n"
"uniform mat4 modelMatrixBox;                                          \n"
"uniform mat4 inverseViewMatrix;                                        \n"
"uniform vec3 diffuse_color;                                          \n"
"uniform vec3 ambient_color;                                          \n"
"uniform vec3 specular_color;                                          \n"
"uniform vec4 light_position;                                          \n"
"uniform float diffuse_intensity;                                          \n"
"uniform float ambient_intensity;                                          \n"
"uniform float specular_intensity;                                          \n"
"uniform float shininess;                                          \n"
"in vec3 in_Position;                                               \n"
"in vec3 in_Normal;                                                  \n"
"in vec3 in_Color;                                                  \n"
"                                                                  \n"
"                                                                 \n"
"                                                                 \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    vec3 normal = normalize(in_Normal);                                                                        \n"
"    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));             \n"
"    vec4 surfacePostion = viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);                             \n"
"                                                                                                               \n"
"    vec4 surface_to_light =   normalize( light_position -  surfacePostion );                         \n"
"                                                                                                               \n"
"    // Diffuse color                                                                                           \n"
"    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                           \n"
"    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;                         \n"
"                                                                                                               \n"
"    // Ambient color                                                                                           \n"
"    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;                                          \n"
"                                                                                                               \n"
"    // Specular color                                                                                          \n"
"    vec3 incidenceVector = -surface_to_light.xyz;                                                              \n"
"    vec3 reflectionVector = reflect(incidenceVector, normal);                                   \n"
"    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);             \n"
"    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                     \n"
"    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                        \n"
"    float specular_coefficient = pow(cosAngle, shininess);                                                     \n"
"    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;                      \n"
"                                                                                                               \n"
"    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);               \n"
"                                                                                                               \n"
"    gl_FrontColor = vec3(out_diffuse_color + out_ambient_color + out_specular_color);                          \n"
"}                                                                                                              \n";




// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string_GLDia_410  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";


static const string fs_string_GLDia_300  =
"#version 310 core                                                 \n"
"                                                                  \n"
"                                                                   \n"
"                                                                   \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_FragColor = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";










GLDiamond::GLDiamond(float vertex_x, float vertex_y, float vertex_z, float size)
{
    
    _vertex.x() = vertex_x;
    _vertex.y() = vertex_y;
    _vertex.z() = vertex_z;
    
    _size = size;

    
    _render_normal_vectors = false;
    _program_normals = -1;
    _program = -1;
    
    initShader();
    initVBO();

    initShaderNormal();
    initVBONormals();

}




GLDiamond::~GLDiamond()
{
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, _vaoID);
    glDeleteVertexArrays(1, _vaoIDNormals);
    glDeleteProgram(_program);
    glDeleteProgram(_program_normals);
}


/*!
 Draw the objects
 */
void GLDiamond::draw(void)
{
 
    //////////////////////////////////////////////////
    // Renders the sphere
    
    // Enable the shader program
    glUseProgram(_program);
	
    // this changes the camera location
    glm::mat4 rotated_view =  rotatedViewMatrix();
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
    glUniformMatrix4fv(_inverseViewMatrixLocation, 1, GL_FALSE, &invRotatedViewMatrix()[0][0]);
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); //
    
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(_vaoID[0]);
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // allows to see the primitives

    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 7);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 7);
	glDrawArrays(GL_TRIANGLES, 22, 6);
    
    //////////////////////////////////////////////////
    // Renders the normal vectors
    
    if(_render_normal_vectors)
    {
    
        // Enable the shader program
        glUseProgram(_program_normals);
    
        glUniformMatrix4fv(_viewMatrixLocationN, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        glUniformMatrix4fv(_modelMatrixLocationN, 1, GL_FALSE, &_modelMatrix[0][0]); //
    
    
        // Bind the buffer and switch it to an active buffer
        glBindVertexArray(_vaoIDNormals[0]);
        glDrawArrays(GL_LINES, 0, _num_vertices_normals);
    }
    
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
    
    // Unbind the shader program
    glUseProgram(0);
    
    
}

/*!
 Set the model matrix for this object
 @param modelmatrix: 4x4 model matrix
 */
void GLDiamond::setModelMatrix(glm::mat4& modelmatrix)
{
    _modelMatrix=modelmatrix;
    
}


/*!
 Enables or disables the normal vector renderer
 @param value = true -> enables the renderer, false -> disables the renderer
 */
void GLDiamond::enableNormalVectorRenderer(bool value )
{
    _render_normal_vectors = value;
}


/*!
 Create the vertex buffer object for this element
 */
void GLDiamond::initVBO(void)
{

    
    _diaPoints.clear();
    _normalVectors.clear();
    
    make_Dia(_vertex, _size, _diaPoints, _normalVectors);
    
    _num_vertices = _diaPoints.size();
    
    // create memory for the vertices, etc.
    float* vertices = new float[_diaPoints.size() * 3];
    float* colors = new float[_diaPoints.size() * 3];
    float* normals = new float[_diaPoints.size() * 3];
    
    
    // copy the data to the vectors
    for(int i=0; i<_diaPoints.size() ; i++)
    {
        Vertex v = _diaPoints[i];
        vertices[(i*3)] = v.x(); vertices[(i*3)+1] = v.y(); vertices[(i*3)+2] = v.z();
        
        Vertex n = _normalVectors[i];
        normals[(i*3)] = n.x(); normals[(i*3)+1] = n.y(); normals[(i*3)+2] = n.z();
        
        colors[(i*3)] = 1.0; colors[(i*3)+1] = 1.0; colors[(i*3)+2] = 0.0;
    }
    
    glUseProgram(_program);
    
    
    glGenVertexArrays(1, _vaoID); // Create our Vertex Array Object
    glBindVertexArray(_vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(3, _vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int locPos = glGetAttribLocation(_program, "in_Position");
    glVertexAttribPointer((GLuint)locPos, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(locPos); //
    
    
    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 3 *  sizeof(GLfloat), normals, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int locNorm = glGetAttribLocation(_program, "in_Normal");
    glVertexAttribPointer((GLuint)locNorm, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(locNorm); //
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[2]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 3 *  sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int logColor = glGetAttribLocation(_program, "in_Color");
    glVertexAttribPointer((GLuint)logColor, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(logColor); //
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    // delete the memory
    delete vertices;
    delete colors;
    delete normals;
}


/*!
 Init a frame buffer object to draw normal vectors
 */
void GLDiamond::initVBONormals(void)
{
    
    // create the normal vector lines
    vector<Vertex> normalVectorLines;
    for(int i=0; i<_diaPoints.size() ; i++)
    {
        Vertex v = _diaPoints[i];
        Vertex n = _normalVectors[i];
        
        normalVectorLines.push_back(v);
        normalVectorLines.push_back(v+n);
        
    }
    
    float *normal_lines = new float[normalVectorLines.size() * 3];
    float *colors = new float[normalVectorLines.size() * 3];

    for(int i=0; i<normalVectorLines.size() ; i++)
    {
        normal_lines[(i*3)] = normalVectorLines[i].x();
        normal_lines[(i*3)+1] = normalVectorLines[i].y();
        normal_lines[(i*3)+2] = normalVectorLines[i].z();
        
        colors[(i*3)] = 0.0; colors[(i*3)+1] = 0.0; colors[(i*3)+2] = 1.0;
    }
    
    _num_vertices_normals = normalVectorLines.size();
    
    glUseProgram(_program_normals);
    
    glGenVertexArrays(1, _vaoIDNormals); // Create our Vertex Array Object
    glBindVertexArray(_vaoIDNormals[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, _vboIDNormals); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vboIDNormals[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, normalVectorLines.size() * 3 * sizeof(GLfloat), normal_lines, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); //
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, _vboIDNormals[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, normalVectorLines.size() * 3 *  sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)glGetAttribLocation(_program, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(glGetAttribLocation(_program, "in_Color")); //
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    delete normal_lines;
    delete colors;
}


/*
 Inits the shader program for this object
 */
void GLDiamond::initShader(void)
{
    
    if(!_apperance.exists())return;
    
    // This loads the shader program from a file
    _program = _apperance.getProgram();
    
    
    glUseProgram(_program);
    
    
    _modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    
    
    int projectionMatrixLocation = glGetUniformLocation(_program, "projectionMatrixBox"); // Get the location of our projection matrix in the shader
    _viewMatrixLocation = glGetUniformLocation(_program, "viewMatrixBox"); // Get the location of our view matrix in the shader
    _modelMatrixLocation = glGetUniformLocation(_program, "modelMatrixBox"); // Get the location of our model matrix in the shader
    _inverseViewMatrixLocation = glGetUniformLocation(_program, "inverseViewMatrix");
    
    _light_source0._lightPosIdx = glGetUniformLocation(_program, "light_position");
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
     glUniformMatrix4fv(_inverseViewMatrixLocation, 1, GL_FALSE, &invRotatedViewMatrix()[0][0]);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Material
    _material._diffuse_material = glm::vec3(1.0, 0.5, 0.0);
    _material._ambient_material = glm::vec3(1.0, 0.5, 0.0);
    _material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    _material._shininess = 12.0;
    
    
    _material._ambientColorPos = glGetUniformLocation(_program, "ambient_color");
    _material._diffuseColorPos = glGetUniformLocation(_program, "diffuse_color");
    _material._specularColorPos = glGetUniformLocation(_program, "specular_color");
    _material._shininessIdx = glGetUniformLocation(_program, "shininess");
    
    
    // Send the material to your shader program
    glUniform3fv(_material._ambientColorPos, 1, &_material._ambient_material[0] );
    glUniform3fv(_material._diffuseColorPos, 1, &_material._diffuse_material[0]);
    glUniform3fv(_material._specularColorPos, 1, &_material._specular_material[0]);
    glUniform1f(_material._shininessIdx, _material._shininess);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Light
    
    // define the position of the light and send the light position to your shader program
    _light_source0._lightPos = glm::vec4(50.0,50.0,0.0,1.0);
    _light_source0._ambient_intensity = 0.5;
    _light_source0._specular_intensity = 1.0;
    _light_source0._diffuse_intensity = 1.0;
 
    

    _light_source0._ambientIdx = glGetUniformLocation(_program, "ambient_intensity");
    _light_source0._diffuseIdx = glGetUniformLocation(_program, "diffuse_intensity");
    _light_source0._specularIdx = glGetUniformLocation(_program, "specular_intensity");
   
    

    // Send the light information to your shader program
    glUniform1f(_light_source0._ambientIdx, _light_source0._ambient_intensity );
    glUniform1f(_light_source0._diffuseIdx, _light_source0._diffuse_intensity);
    glUniform1f(_light_source0._specularIdx, _light_source0._specular_intensity);
    
    glUniform4fv(_light_source0._lightPosIdx, 1, &_light_source0._lightPos[0]);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Vertex information / names
    // bind the to the shader program
    glBindAttribLocation(_program, 0, "in_Position");
    glBindAttribLocation(_program, 1, "in_Normal");
    glBindAttribLocation(_program, 2, "in_Color");
    
    
    
     glUseProgram(0);
    
}



/*!
 Shader for the normal vector renderer
 */
void GLDiamond::initShaderNormal(void)
{
    _program_normals = CreateShaderProgram(vs_string_simple_shader_410, fs_string_simple_shader_410);
    
    glUseProgram(_program_normals);
    
    unsigned int projectionMatrixLocation = glGetUniformLocation(_program_normals, "projectionMatrix"); // Get the location of our projection matrix in the shader
    _viewMatrixLocationN = glGetUniformLocation(_program_normals, "viewMatrix"); // Get the location of our view matrix in the shader
    _modelMatrixLocationN = glGetUniformLocation(_program_normals, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocationN, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocationN, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    glBindAttribLocation(_program_normals, 0, "in_Position");
    glBindAttribLocation(_program_normals, 1, "in_Color");

    glUseProgram(0);
}




void GLDiamond::make_Dia(Vertex center, double r, std::vector<Vertex> &diaPoints, std::vector<Vertex> &normals)
{
    const double PI = 3.141592653589793238462643383279502884197;
	float vertices_of_obj[11][3] = {
	{0.0f, 0.0f, 0.0f},  //0
	{0.5f, 0.866f, 1.5f},
	{1.0f, 0.0f, 1.5f},
	{0.5f, -0.866f, 1.5f},
	{-0.5f, -0.866f, 1.5f},  
	{-1.0f, 0.0f, 1.5f},
	{-0.5f, 0.866f, 1.5f},//6
	{0.0f, 0.5f, 2.0f},
	{0.5f, 0.0f, 2.0f},
	{0.0f, -0.5f, 2.0f},  
	{-0.5f, 0.0f, 2.0f}//10
	};

    diaPoints.clear();
	normals.clear();

	int vertices_sequence[28] = {
		0,1,2,3,4,5,6,1, // fan 1, size 8
		8,2,3,9,7,1,2, // fan 2, size 7
		10,9,4,5,6,7,9, // fan 3, size 7
		7,1,6,  // tri 1
		9,3,4 // tri 2
	};

    
    int current_size = 0;
    for (int i = 0; i < 28; i++) 
    {  
        Vertex point;
        point.x() = vertices_of_obj[vertices_sequence[i]][0] * _size + center.x();
        point.y() = vertices_of_obj[vertices_sequence[i]][1] * _size + center.y();
        point.z() = vertices_of_obj[vertices_sequence[i]][2] * _size + center.z();
        diaPoints.push_back(point);       
    }
	//for(int i = 0; i < 28; i++)
	//{
	//    Vertex normal;
	//	normal.x() =  diaPoints[i].x();
	//    normal.y() =  diaPoints[i].y();
	//	normal.z() =  diaPoints[i].z()-1.5* _size;
	//    normals.push_back(normal);   
	//}
	// fan 1, size 8
	normals.push_back(Vertex(0,0,0));
	normals.push_back(Vertex(0,0,0));
	for(int i = 2; i < 8; i++)
	{
		glm::vec3 vec0(vertices_of_obj[vertices_sequence[0]][0],vertices_of_obj[vertices_sequence[0]][1],vertices_of_obj[vertices_sequence[0]][2]);
		glm::vec3 vec1(vertices_of_obj[vertices_sequence[i]][0],vertices_of_obj[vertices_sequence[i]][1],vertices_of_obj[vertices_sequence[i]][2]);
		glm::vec3 vec2(vertices_of_obj[vertices_sequence[i-1]][0],vertices_of_obj[vertices_sequence[i-1]][1],vertices_of_obj[vertices_sequence[i-1]][2]);
		
		glm::vec3 nor = glm::cross((vec1-vec0), (vec2-vec0));
		nor = glm::normalize(nor);
		float sign = nor[2]/std::abs(nor[2]);

        Vertex normal;
		normal.x() =  -nor[0]*sign;
        normal.y() =  -nor[1]*sign;
		normal.z() =  -nor[2]*sign;
        normals.push_back(normal);   
	}
	// fan 2, size 7
	normals.push_back(Vertex(0,0,0));
	normals.push_back(Vertex(0,0,0));
	for(int i = 10; i < 15; i++)
	{
		glm::vec3 vec0(vertices_of_obj[vertices_sequence[8]][0],vertices_of_obj[vertices_sequence[8]][1],vertices_of_obj[vertices_sequence[8]][2]);
		glm::vec3 vec1(vertices_of_obj[vertices_sequence[i]][0],vertices_of_obj[vertices_sequence[i]][1],vertices_of_obj[vertices_sequence[i]][2]);
		glm::vec3 vec2(vertices_of_obj[vertices_sequence[i-1]][0],vertices_of_obj[vertices_sequence[i-1]][1],vertices_of_obj[vertices_sequence[i-1]][2]);
		
		glm::vec3 nor = glm::cross((vec1-vec0), (vec2-vec0));
		nor = glm::normalize(nor);
		float sign = nor[2]/std::abs(nor[2]);

        Vertex normal;
		normal.x() =  nor[0]*sign;
        normal.y() =  nor[1]*sign;
		normal.z() =  nor[2]*sign;
        normals.push_back(normal);   
	}
	// fan 3, size 7
	normals.push_back(Vertex(0,0,0));
	normals.push_back(Vertex(0,0,0));
	for(int i = 17; i < 22; i++)
	{
		glm::vec3 vec0(vertices_of_obj[vertices_sequence[15]][0],vertices_of_obj[vertices_sequence[15]][1],vertices_of_obj[vertices_sequence[15]][2]);
		glm::vec3 vec1(vertices_of_obj[vertices_sequence[i]][0],vertices_of_obj[vertices_sequence[i]][1],vertices_of_obj[vertices_sequence[i]][2]);
		glm::vec3 vec2(vertices_of_obj[vertices_sequence[i-1]][0],vertices_of_obj[vertices_sequence[i-1]][1],vertices_of_obj[vertices_sequence[i-1]][2]);
		
		glm::vec3 nor = glm::cross((vec1-vec0), (vec2-vec0));
		nor = glm::normalize(nor);
		float sign = nor[2]/std::abs(nor[2]);

        Vertex normal;
		normal.x() =  nor[0]*sign;
        normal.y() =  nor[1]*sign;
		normal.z() =  nor[2]*sign;
        normals.push_back(normal);   
	}
	// tri 1
	for(int i = 22; i < 25; i++)
	{
		glm::vec3 vec0(vertices_of_obj[vertices_sequence[22]][0],vertices_of_obj[vertices_sequence[22]][1],vertices_of_obj[vertices_sequence[22]][2]);
		glm::vec3 vec1(vertices_of_obj[vertices_sequence[23]][0],vertices_of_obj[vertices_sequence[23]][1],vertices_of_obj[vertices_sequence[23]][2]);
		glm::vec3 vec2(vertices_of_obj[vertices_sequence[24]][0],vertices_of_obj[vertices_sequence[24]][1],vertices_of_obj[vertices_sequence[24]][2]);
		
		glm::vec3 nor = glm::cross((vec1-vec0), (vec2-vec0));
		nor = glm::normalize(nor);
		float sign = nor[2]/std::abs(nor[2]);

        Vertex normal;
		normal.x() =  nor[0]*sign;
        normal.y() =  nor[1]*sign;
		normal.z() =  nor[2]*sign;
        normals.push_back(normal);   
	}
	// tri 1
	for(int i = 25; i < 28; i++)
	{
		glm::vec3 vec0(vertices_of_obj[vertices_sequence[25]][0],vertices_of_obj[vertices_sequence[25]][1],vertices_of_obj[vertices_sequence[25]][2]);
		glm::vec3 vec1(vertices_of_obj[vertices_sequence[26]][0],vertices_of_obj[vertices_sequence[26]][1],vertices_of_obj[vertices_sequence[26]][2]);
		glm::vec3 vec2(vertices_of_obj[vertices_sequence[27]][0],vertices_of_obj[vertices_sequence[27]][1],vertices_of_obj[vertices_sequence[27]][2]);
		
		glm::vec3 nor = glm::cross((vec1-vec0), (vec2-vec0));
		nor = glm::normalize(nor);
		float sign = nor[2]/std::abs(nor[2]);

        Vertex normal;
		normal.x() =  nor[0]*sign;
        normal.y() =  nor[1]*sign;
		normal.z() =  nor[2]*sign;
        normals.push_back(normal);   
	}
    return;
}




