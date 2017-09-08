#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Draw.h"
#include "graphics\genShape.h"
#include "graphics\Load.h"

#include"glm/ext.hpp"

void main()
{

	Context context;
	context.init();
	Framebuffer fb_shadow = MakeFrameBuffer(2048, 2048, 0, true, 0, 0);
	Framebuffer screen = { 0,800,600 };

	Vertex vquad[] =
	{
		{{-1,-1, 0, 1}, {},  {0,0}, {0,0,1,0}},
		{{1, -1, 0, 1}, {},  {1,0}, {0,0,1,0}},
		{{1,  1,  0, 1}, {}, {1,1}, {0,0,1,0}},
		{{-1, 1,  0, 1}, {}, {0,1}, {0,0,1,0}}
	};

	unsigned quadidx[] = { 0,1,3,1,2,3 };
	solveTangents(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model;

	//Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	//Camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, screen.width / (float)screen.height, 1.f, 10.f);

	//Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8f, -1.f, -1.f));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//Shaders
	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert", "../../resources/shaders/shadow.frag");

	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert", "../../resources/shaders/direct.frag");

	int loc = 0, slot = 0;

	while (context.step())
	{
		float time = context.getTime();

		//Shadow Pass
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow);

		//draw floor 
		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);


		//soulspear
		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);

		//cube
		loc = 0, slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, cube_model);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);

		//Light pass
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, floor_model, light_proj, light_view, fb_shadow.depthTarget);
		s0_draw(screen, shdr_direct, floor_geo);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, floor_model, light_view, fb_shadow.depthTarget);
		s0_draw(screen, shdr_direct, floor_geo);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, ss_model, light_view, fb_shadow.depthTarget);
		s0_draw(screen, shdr_direct, ss_geo);

		loc = 0, slot = 0;
		setUniforms(shdr_direct, loc, slot, cam_proj, cam_view, cube_model, light_view, fb_shadow.depthTarget);
		s0_draw(screen, shdr_direct, cube_geo);




	}

	context.term();
	
	
}