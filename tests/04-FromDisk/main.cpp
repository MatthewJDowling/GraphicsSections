

#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"


int main()
{
	Context context;
	context.init(800, 800);

	Texture tex = loadTexture("../../resources/textures/spriteSheet.png");

	Vertex vquad[] = {
		{{-1,-1,0,1},  {},{0,0}},
		{{1,-1,0,1} ,  {},{1,0}},
		{{1,1,0,1}  ,  {},{1,1}},
		{{-1,1,0,1} ,  {}, {0,1}}
		};
	
	unsigned quadix[] = { 0,1,3,1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadix, 6);

	/*const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec2 vUV;\n"
		"void main () \n"
		"{\n"
		"gl_Position = position; vUV = texCoord;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec2 vUV;\n"
		"layout(location = 0) uniform sampler2D map;\n"
		"void main () \n"
		"{\n"
		"outColor = texture(map, vUV.xy);\n"
		"}\n";*/
/*
	Shader sq = makeShader(vsource, fsource);*/

	Shader sq = loadShader("../../resources/shaderhj b s/test.vert", "../../resources/shaders/test.frag");

	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Framebuffer screen = { 0,800,800 };

	while (context.step())
	{
		clearFramebuffer(screen);

		int loc = 0, tslot = 0;

		setUniforms(sq, loc, tslot, tex);

		s0_draw(screen, sq, cube);
	}
		
	context.term();
	return 0;
}