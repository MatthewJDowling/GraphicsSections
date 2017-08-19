#include <iostream>
#include "graphics\Draw.h"
#include "graphics\Vertex.h"
#include "graphics\Context.h"
#include "graphics\genShape.h"
#include "graphics\RenderObjects.h"
int main()
{
	Context context;
	context.init(800, 600);

	context.createCustomCursor();
						//vertices			color
	Vertex verts[4] = { {{-.5f,-.5f,0,1,} ,{1,0,1,1}},//bottom left
						{{ .5f,-.5f,0,1}  ,{0,1,1,1}},//bottom right
						{{ .5f, .5f,0,1}  ,{1,1,0,1}},//top right
						{{-.5f, .5f,0,1}  ,{0,0,1,1}}};//top left


	unsigned idxs[6] = { 0,1,2,3,2,0 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);
	Geometry gt = makeCheckerboard(1, 1);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"flat out vec4 vColor;\n"
		"void main ()\n"
		"{gl_Position = position;  vColor = color;}\n";
		
		


	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"flat in vec4 vColor;\n"
		"void main ()\n"
		"{outColor = vColor;} \n";

	Shader s = makeShader(vsource, fsource);

	Framebuffer f = { 0, 800, 600 };


	while (context.step())
	{
		//std::cout << context.getKey('K') << std::endl; 
		//std::cout << context.getTime() << std::endl;
		//s0_draw(f, s, g);
		s0_draw(f, s, gt);
	}
	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}