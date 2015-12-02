#version 410 core                                                 

// Transformations for the projections
uniform mat4 projectionMatrixBox2;                                    
uniform mat4 viewMatrixBox2;                                          
uniform mat4 modelMatrixBox2;     

// The material parameters 
uniform vec3 diffuse_color2;                                        
uniform vec3 ambient_color2;                                         
uniform vec3 specular_color2;   

// Position of the light source
uniform vec4 light_position2;   

// The intensity values for the reflection equations
uniform float diffuse_intensity2;                                          
uniform float ambient_intensity2;                                        
uniform float specular_intensity2;                                       
uniform float shininess2;    
uniform float attenuationCoefficient2;                                    
                                              
// The vertex buffer input                                    
in vec3 in_Color; 
in vec3 in_Position; 
in vec3 in_Normal;  

// The output color
out vec3 pass_Color;                                            
                                                                 
                                                               
                                                                                                                               
void main(void)                                                 
{                                                               
	vec3 normal = normalize(in_Normal);                                                                   
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox2)) * vec4( normal, 1.0 ));            
    vec4 surfacePostion = modelMatrixBox2 * vec4(in_Position, 1.0);                          
                                                                                                            
    vec4 surface_to_light =   normalize( light_position2 -  surfacePostion );                      
                                                                                                            
    // Diffuse color                                                                                          
    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                         
    vec3 out_diffuse_color2 = diffuse_color2  * diffuse_coefficient * diffuse_intensity2;                        
                                                                                                              
    // Ambient color                                                                                         
    vec3 out_ambient_color2 = vec3(ambient_color2) * ambient_intensity2;                                        
                                                                                                             
    // Specular color                                                                                        
    vec3 incidenceVector = -surface_to_light.xyz;                                                             
    vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);                                   
    vec3 cameraPosition = vec3( -viewMatrixBox2[3][0], -viewMatrixBox2[3][1], -viewMatrixBox2[3][2]);            
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                   
    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                       
    float specular_coefficient = pow(cosAngle, shininess2);                                                     
    vec3 out_specular_color2 = specular_color2 * specular_coefficient * specular_intensity2;                    
  
	
	//attenuation
    float distanceToLight = length(light_position2.xyz - surfacePostion.xyz);
    float attenuation = 1.0 / (1.0 + attenuationCoefficient2 * pow(distanceToLight, 2));
	
	//////////////////////////////////////////////////////////////////////////////////////////////        
    // Directional light
    //
	if(light_position2.w == 0.0) {
 	    // this is a directional light.

		// 1. the values that we store as light position is our light direction.
  		vec3 light_direction = normalize(light_position2.xyz);
  		
  		// 2. We check the angle of our light to make sure that only parts towards our light get illuminated
  		float light_to_surface_angle = dot(light_direction, transformedNormal.xyz);
  		
  		// 3. Check the angle, if the angle is smaller than 0.0, the surface is not directed towards the light. 
  		if(light_to_surface_angle > 0.0)attenuation = 1.0;
  		else attenuation = 0.0;	
	} 
	
	
	// Calculate the linear color
	vec3 linearColor = out_ambient_color2  + attenuation * ( out_diffuse_color2 + out_specular_color2);  
	
	// Gamma correction	
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor = pow(linearColor, gamma);
	
	// Pass the color 
	pass_Color =  finalColor;
	
	// Passes the projected position to the fragment shader / rasterization process. 
    gl_Position = projectionMatrixBox2 * viewMatrixBox2 * modelMatrixBox2 * vec4(in_Position, 1.0);             
                                                                                                             
                          
}                                                                                                            