#version 330 core

//  Changes made for class
//	ME 557
//	10 / 8 / 2015
//	By: Michael Hoefer, Anupu Prudhivi, and Hsin Miao Lee
//
// The vertex buffer input                                    
in vec3 in_Color; 
in vec3 in_Position; 
in vec3 in_Normal;  

// Transformations for the projections
uniform mat4 projectionMatrixBox;
uniform mat4 viewMatrixBox;
uniform mat4 modelMatrixBox;

// The material parameters 
uniform vec3 diffuse_color;                                        
uniform vec3 ambient_color;                                         
uniform vec3 specular_color;   

// Position of the light source
uniform vec4 light_position;   

// New parameters for the spotlight
uniform float cone_angle;
uniform float cone_angle2;
uniform vec3 cone_direction;

// The intensity values for the reflection equations
uniform float diffuse_intensity;                                          
uniform float ambient_intensity;                                        
uniform float specular_intensity;                                       
uniform float shininess;    
uniform float attenuationCoefficient;                                    
                                              



// The output color
out vec3 pass_Color;                                            
                                                                 
             
float smoothstep(float edge0, float edge1, float x)
{
	x = clamp((x - edge0)/(edge1 - edge0), 0.0, 1.0);
	return x*x*(3 - 2*x);
}			 
                                                                                                                               
void main(void)                                                 
{                                                               
	vec3 normal = normalize(in_Normal);                                                                   
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));            
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);                          
                                                                                                       
    vec4 surface_to_light =   normalize( light_position -  surfacePostion );                      
                                                                                                            
    // Diffuse color                                                                                          
    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                         
    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;                        
                                                                                                              
    // Ambient color                                                                                         
    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;                                        
                                                                                                             
    // Specular color                                                                                        
    vec3 incidenceVector = -surface_to_light.xyz;                                                             
    vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);                                   
    vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);            
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                   
    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                       
    float specular_coefficient = pow(cosAngle, shininess);                                                     
    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;                    
  
	
	//attenuation
    float distanceToLight = length(light_position.xyz - surfacePostion.xyz);
    float attenuation = 1.0 / (1.0 + attenuationCoefficient * pow(distanceToLight, 2));
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////        
    // Spotlight
    // 1. Normalize the cone direction
    vec3 cone_direction_norm = normalize(cone_direction); 
    
    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    vec3 ray_direction = -surface_to_light.xyz;   
    
    // 3. Calculate the angle between light and surface using the dot product again. 
    //    To simplify our understanding, we use the degrees
    float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ; 
    
	
	//3.5 calulate smooth spotlight
	// cone_angle = edge0, cone_angle2 = edge1
	if(light_to_surface_angle > cone_angle && light_to_surface_angle < cone_angle2){
  			
			attenuation = ((cone_angle2 - light_to_surface_angle)/(cone_angle2 - cone_angle))*attenuation;
			//attenuation = clamp((attenuation - cone_angle)/(cone_angle - cone_angle2), 0.0, 1.0);
			//attenuation = attenuation*attenuation*(3 - 2*attenuation);
		
	}
	
    // 4. Last, we compare the angle with the current direction and 
    //    reduce the attenuation to 0.0 if the light is outside the angle. 
	if(light_to_surface_angle > cone_angle2){
  		attenuation = 0.0;
	}
	
	
	// Calculate the linear color
	vec3 linearColor = out_ambient_color  + attenuation * ( out_diffuse_color + out_specular_color);  
	
	// Gamma correction	
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor = pow(linearColor, gamma);
	
	// Pass the color 
	pass_Color =  finalColor;
	
	// Passes the projected position to the fragment shader / rasterization process. 
    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);                                                                                                                   
                          
}                                                                                                            