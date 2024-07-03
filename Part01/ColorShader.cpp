#include "ColorShader.hpp"

ColorShader::ColorShader() {

}

// constructor that allows for vertex and fragment shaders with different names.
ColorShader::ColorShader(std::string vertexshaderName, std::string fragmentshaderName): Shader(vertexshaderName, fragmentshaderName) {

	colorID = glGetUniformLocation(programID, "colorValue");
	glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glProgramUniform4fv(programID, colorID, 1, &color[0]);

}

// constructor that assumes that vertex and fragment shader have same name
ColorShader::ColorShader(std::string shaderName): Shader(shaderName) {

	colorID = glGetUniformLocation(programID, "colorValue");
	glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glProgramUniform4fv(programID, colorID, 1, &color[0]);

}

ColorShader::~ColorShader() {

	glDeleteProgram(programID);

}

void ColorShader::setColor(glm::vec4 newColor) {

	glProgramUniform4fv(programID, colorID, 1, &newColor[0]);

}

void ColorShader::bind() {

    // Use our shader
    glUseProgram(programID);

}