 #include <iostream>
#include "graphics\Draw.h"
#include "glm/glm.hpp"
#include "glm\ext.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\genShape.h"
#include "graphics\RenderObjects.h"
int main()
{
	Context context;
	context.init(800, 600);

	context.createCustomCursor();
	//vertices			         color       UVs
	Vertex verts[4] = { { { -.5f,-.5f,0,1, } ,{ 1,0,0,1 },{ 0,0 } },//bottom left
	{ { .5f,-.5f,0,1 }     ,{ 1,1,0,1 },{ 1,0 } },//bottom right
	{ { .5f, .5f,0,1 }     ,{ 0,1,1,1 },{ 1,1 } },//top right
	{ { -.5f, .5f,0,1 }    ,{ 0,0,1,1 },{ 0,1 } } };//top left


	unsigned idxs[6] = { 0,1,2,3,2,0 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);
	//Geometry gt = makeCheckerboard(1, 1);

	Framebuffer f = { 0, 800, 600 };


	//RGB texture (3 channels), 2x1
	unsigned char pixels[] = { 51,0,255,255,36,0 };

	Texture t_magyel = makeTexture(2, 1, 3, pixels);


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 6) uniform mat4 model;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = model * position;"
		"}\n";




	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform  int k0;\n"
		"layout(location = 1) uniform int k1;\n"
		"layout(location = 2) uniform int k2;\n"

		"layout(location = 3) uniform vec4 c0 = vec4(1,0,0,1);\n"
		"layout(location = 4) uniform vec4 c1 = vec4(0,1,0,1);\n"
		"layout(location = 5) uniform vec4 c2 = vec4(0,0,1,1);\n"
		"void main ()\n"
		"{\n"
		"outColor = c0*(1-k0) + c1*(1-k1) + c2*(1-k2); "
		"} \n";


	Shader s = makeShader(vsource, fsource);


	

	while (context.step())
	{
		clearFramebuffer(f);

		glm::mat4 rot = glm::translate(glm::vec3(.5, 0, 0)) * 
			glm::rotate((float)context.getTime(), glm::vec3(0.f, 0.f, 1.f)) * 
			glm::scale(glm::vec3(.5, .5, 1));

		int loc = 0, tex = 0;
		setUniforms(s, loc, tex, (int)context.getKey('W'), (int)context.getKey('S'), (int)context.getKey('D'),
			glm::vec4(1, 1, 1, 1), glm::vec4(1, 0, 1, 1), rot);

		
		s0_draw(f, s, g);
		//	s0_draw(f, s2, g);
	}
	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);

	context.term();
	return 0;
}