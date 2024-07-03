#define COLORSHADER_HPP

//include the shader header file
#include "Common/Shader.hpp"

//!  ColorShader.
/*!
Shader of a singular color. constructor accepts a glm::vec4 color value.
 */
class ColorShader : public Shader {
	public:

	//default constructor
	ColorShader();
	//
	//! ColorShader
	/*! constructor that allows for vertex and fragment shaders with different names. */
	ColorShader(std::string vertextshaderName, std::string fragmentshaderName);
	//! ColorShader
	/*! constructor that assumes that vertext and fragment shader have same name. */
	ColorShader(std::string shaderName);

	//! Destructor
	~ColorShader();
	//! setColor
	/*! Set a reference to the Color. */
	void setColor(glm::vec4 color);
	//! bind
	/*! Bind the shader. */
	void bind();

	private:
		glm::vec4 color;
		glm::vec4 newColor;
		GLint colorID;
};