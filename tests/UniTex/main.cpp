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
										//vertices			         color       UVs
	Vertex verts[4] =					{ { { -.5f,-.5f,0,1, } ,   { 1,0,0,1 },  {0,0} },//bottom left
										{ { .5f,-.5f,0,1 }     ,   { 1,1,0,1 },  {1,0} },//bottom right
										{ { .5f, .5f,0,1 }     ,   { 0,1,1,1 },  {1,1} },//top right
										{ { -.5f, .5f,0,1 }    ,   { 0,0,1,1 },  {0,1} } };//top left


	unsigned idxs[6] = { 0,1,2,3,2,0 };

	Geometry g = makeGeometry(verts, 4, idxs, 6);
	//Geometry gt = makeCheckerboard(1, 1);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 textureCoordinate;\n"

		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int press;\n"
		"layout(location = 2) uniform int press2;\n"

		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{gl_Position = position;\n"
		"vUV = textureCoordinate;\n"
		"gl_Position.x += cos(time) / gl_Position.y / 100 + press;\n"
		"gl_Position.x += cos(time) / gl_Position.y / 100 - press2;\n"
		"gl_Position.y += cos(time) / gl_Position.y / 50 + press; \n"
		"gl_Position.y += cos(time) / gl_Position.y / 50 - press2;\n"
		
		"vColor = vec4 (0,0 ,cos(time) +gl_Position.y ,1);}\n";




	const char* fsource =
		"#version 450\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform float time;\n"
		" in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"vec2 uv = vUV;"
		"uv.x += 2 * sin(uv.x * time   + 2) + (uv.y + 2);\n"
		"uv.y += 2 * sin(uv.y * time  + 2) + (uv.x + 2);\n"
		"outColor = texture(map, uv);\n"
		"} \n";
	

	Shader s = makeShader(vsource, fsource);


	Framebuffer f = { 0, 800, 600 };


	//RGB texture (3 channels), 2x1
	unsigned char pixels[] = { 51,0,255,255,36,0 };

	Texture t_magyel = makeTexture(2, 1, 3, pixels);


	while (context.step())
	{
		clearFramebuffer(f);
		setUniform(s, 0, (float)context.getTime());
		

		setUniform(s, 4, t_magyel, 0);
	
		s0_draw(f, s, g);
	//	s0_draw(f, s2, g);
	}
	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}