#version 330 core

// Ouput data
out vec3 outcolor;

//uniform data
uniform vec4 colorValue;

void main()
{

	// Output color
	outcolor = colorValue.rgb;

}