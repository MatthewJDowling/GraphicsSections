#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Draw.h"
#include "graphics\genShape.h"
#include "graphics\Load.h"

#include"glm/ext.hpp"
int main()
{
	Context context;
	context.init(1200, 1200);
	

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };



	Framebuffer f = { 0,800,1200 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);


	Texture tex = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Geometry model = loadGeometry("../../resources/models/soulspear.obj");
	Shader shade = loadShader("../../resources/shaders/lambert.vert", "../../resources/shaders/lambert.frag");

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 1200.f, .01f, 100.f);
	glm::mat4 go_model; // identity matrix for now

	glm::vec3 dl_dir = glm::normalize(glm::vec3(1, -1, 1));
	glm::vec4 dl_col = glm::vec4(.7f, .6f, .2f, 1.f);

	double x = 0;
	double y = 0;
	while (context.step())
	{
		glm::mat4 go_model = glm::rotate((float)context.getTime(), glm::vec3(1, 1, 1));
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));


		clearFramebuffer(f);
		setFlags(RenderFlag::DEPTH);
		int loc = 0, tslot = 0;
		setUniforms(shade, loc, tslot, cam_proj, cam_view, go_model, tex, dl_dir, dl_col);
		s0_draw(f, shade, model);


	}

	freeGeometry(model);
	freeShader(shade);
	freeTexture(tex);

	context.term();
	return 0;

}