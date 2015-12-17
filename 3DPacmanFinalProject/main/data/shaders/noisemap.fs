#version 410 core                                                 


uniform sampler2D texture_background;
//colorMap;//this is the texture
uniform sampler2D texture_foreground;
//noiseMap;//this is the texture

in vec2 pass_TexCoord;//this is the texture coord
//in vec4 pass_Color;
out vec4 color;
//in vec2 texCoord;
//out vec4 Color;
uniform int texture_blend;

void main (void)
{
	
	
	vec2 noiseVec;

	// Texture function finds the color component for each texture coordinate.

	noiseVec = normalize(texture(texture_background, pass_TexCoord).xy);

        //noiseVec[0]=noiseVec0[0];
	//noiseVec[0]=noiseVec0[1];
	//noiseVec[1]=noiseVec0[2];

	 noiseVec = (noiseVec * 2.0 - 1.0) * 0.055;

        color = texture(texture_foreground, pass_TexCoord + noiseVec);


}