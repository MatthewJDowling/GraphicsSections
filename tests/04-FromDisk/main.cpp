

#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"
#include  "glm\ext.hpp"

int main()
{
	Context context;
	context.init(800, 800);

	Vertex vquad[] = {
		{{-1,-1,0,1},  {},{0,0}},
		{{1,-1,0,1} ,  {},{1,0}},
		{{1,1,0,1}  ,  {},{1,1}},
		{{-1,1,0,1} ,  {}, {0,1}}
		};
	
	unsigned quadix[] = { 0,1,3,1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadix, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");

	Texture tex = loadTexture("../../resources/textures/spriteSheet.png");

	Shader scube = loadShader("../../resources/shaders/cube.vert",
							  "../../resources/shaders/cube.frag");

	Framebuffer screen = { 0,800,800 };

	

	while (context.step())
	{
		clearFramebuffer(screen);

		float time = context.getTime();

		int loc = 0, tslot = 0;
		glm::mat4 mod_cube = glm::rotate(sin(time) * 2, glm::vec3(1, 1, 1));

		setFlags(RenderFlag::DEPTH);


		loc = 0; tslot = 0;
		setUniforms(scube, loc, tslot, mod_cube, tex);

		s0_draw(screen, scube, cube);
	}
		
	context.term();
	return 0;
}