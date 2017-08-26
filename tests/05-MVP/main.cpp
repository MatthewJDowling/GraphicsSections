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
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 } ,{},{ 1,0 } },
		{ { 1,1,0,1 }  ,{},{ 1,1 } },
		{ { -1,1,0,1 } ,{},{ 0,1 } }
	};

	unsigned quadix[] = { 0,1,3,1,2,3 };

	Geometry quad = makeGeometry(vquad, 4, quadix, 6);

	Geometry ss_diffuse = loadGeometry("../../resources/models/soulspear.obj");

	Texture tex = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	Shader scube = loadShader("../../resources/shaders/mvplite.vert",
							 "../../resources/shaders/mvplite.frag");

	Framebuffer screen = { 0,800,800 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 800.f, .01f, 100.f);
	glm::mat4 go_model; 
	glm::mat4 go_model2;
	glm::mat4 go_model3;



	while (context.step())
	{
		float time = context.getTime();
		clearFramebuffer(screen);


		int loc = 0, tslot = 0;
		int loc1 = 0;
		glm::mat4 go_model = glm::rotate(time, glm::vec3(0, 0, 1));
		glm::mat4 go_model2 = glm::translate(glm::vec3(1, 0, 0));
		

		setFlags(RenderFlag::DEPTH);


		setUniforms(scube, loc, tslot, cam_proj, cam_view, go_model, tex);
		s0_draw(screen, scube, ss_diffuse);
		//setUniforms(scube, loc, tslot, mod_cube, tex);

		setUniforms(scube, loc1, tslot, cam_proj, cam_view, go_model2, tex);
		s0_draw(screen, scube, ss_diffuse);


		//setUniforms(scube, loc, tslot, cam_proj, cam_view, go_model3, tex);
		//s0_draw(screen, scube, ss_diffuse);

		
	}

	context.term();
	return 0;
}