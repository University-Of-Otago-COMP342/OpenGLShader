#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <common/Object.hpp>

class Quad: public Object{

	public:
		//! Default Constructor
		Quad();
		//! Destructor
		~Quad();
		//! init
		/*! Setting up default Quad.*/
		void init();
		//! render
		/*! Redner default Quad */
		void render(Camera* camera);

	private:

		GLfloat g_vertex_buffer_data[18];
		GLuint vertexbuffer;

};
