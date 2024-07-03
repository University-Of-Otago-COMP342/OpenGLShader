
/*
 * redTriangle.cpp
 *
 * Adapted from http://opengl-tutorial.org
 * by Stefanie Zollmann
 *
 * Simple Demonstration for getting started with opening a simple window that 
 * does not nothing but rendering a red triangle
 *
 */


/* ------------------------------------------------------------------------- */
/* ---- INCLUDES ----------------------------------------------------------- */
/*
 * Include standard headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>


#include <glad/gl.h>

#define GLAD_GL_IMPLEMENTATION 

/*
 * Include GLFW
 * Multi-platform library for creating windows, contexts and surfaces, receiving input and events.
 */
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include <common/Shader.hpp>
#include <common/Camera.hpp>
#include <common/Scene.hpp>
#include <common/Object.hpp>
#include <common/Triangle.hpp>
#include <Part01/ColorShader.hpp>
#include <Part01/Quad.hpp>

/* ---- Helper Functions  ------------------------------------------------------- */

/*
 *  initWindow
 *
 *  This is used to set up a simple window using GLFW.
 *  Returns true if sucessful otherwise false.
 */
bool initWindow(std::string windowName){
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, windowName.c_str(), NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n" );
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    
    return true;
    
}

/*
 *  main
 *
 *  This is the main function that does all the work.
 *  Creates the window and than calls renderLoop.
 */
int main( void )
{
    
    initWindow("Shader LAB Part 01");
	glfwMakeContextCurrent(window);

	// Initialize glad
	int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.1f, 0.0f, 0.4f, 0.0f);

    
    //create a Vertex Array Object and set it as the current one
    //we will not go into detail here. but this can be used to optimise the performance by storing all of the state needed to supply vertex data
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

    // create a triangle
    Triangle* myTriangle = new Triangle();

    //create two triangles for storing different colors
    Triangle* cyanTriangle = new Triangle();
    //set trigangle position
    //place the triangle at x=-.5
    cyanTriangle->setTranslate(glm::vec3(-.5, 0, 0));
    Triangle* magentaTriangle = new Triangle();
    //set trigangle position
    //place the triangle at x=.5
    magentaTriangle->setTranslate(glm::vec3(.5, 0, 0));

    // create a quad and move it down
    Quad* myQuad = new Quad();
    //set quadlocation
    myQuad->setTranslate(glm::vec3(0, -3, 0));
   
     //the basic vertex shader transforms the vertices using the Model-View Projection matrix
	// and the basic fragment shader outputs a predefined color
    Shader* shader = new Shader( "basicShader");
    //create two shaders that hold the red and blue colors
    ColorShader* cyanShader = new ColorShader("ColorShader");
    ColorShader* magentaShader = new ColorShader("ColorShader");
    //color for quad
    ColorShader* purpleShader = new ColorShader("ColorShader");

    //create the new glm::vec4 colors values
    glm::vec4 cyanColor = glm::vec4(0.0, 1.0, 1.0, 1.0);
    glm::vec4 magentaColor = glm::vec4(1.0, 0.0, 1.0, 1.0);
    glm::vec4 purpleColor = glm::vec4(0.6, 0.3, 0.6, 1.0);
    
    //set the new shaders color values using setColor method
    cyanShader->setColor(cyanColor);
    magentaShader->setColor(magentaColor);
    purpleShader->setColor(purpleColor);

    myTriangle->setShader(shader);
    cyanTriangle->setShader(cyanShader);
    magentaTriangle->setShader(magentaShader);
    myQuad->setShader(purpleShader);

    
    Scene* myScene = new Scene();
    myScene->addObject(myTriangle);
    myScene->addObject(cyanTriangle);
    myScene->addObject(magentaTriangle);
    myScene->addObject(myQuad);
    
    
    Camera* myCamera = new Camera();
    //place the camera at z= -5
	myCamera->setPosition(glm::vec3(0,0,-10));

    
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){// Clear the screen
		
		
		glClear( GL_COLOR_BUFFER_BIT );

		myScene->render(myCamera); // will render all the objects that are part of the scene
		
        glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

    }
    

    glDeleteVertexArrays(1, &VertexArrayID);
	
    delete myScene;
    delete myCamera;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

