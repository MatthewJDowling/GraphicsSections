#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Draw.h"
#include "graphics\genShape.h"
#include "graphics\Load.h"
#include "graphics\GameObjects.h"
#include "graphics\AssMan.h"

#include"glm/ext.hpp"


void main()
{
	Context con;
	con.init(1280, 720);
	// Assman * myass; 
	// Assman::loadModelasset(name,filepath, myass)

	Framebuffer screen = { 0,1280,720 };
	
	AssMan MyManager;

	MyManager.loadModelAsset("soulspear", "../../resources/models/soulspear.obj");
	MyManager.loadTextureAsset("soulspear_normal", "../../resources/textures/soulspear_normal.tga");
	MyManager.loadShaderAsset("shader1", "../../resources/shaders/standard.vert","../../resources/shaders/standard.frag");

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 800.f, .01f, 100.f);
	glm::mat4 model;
	glm::mat4 model2;


	

	while (con.step())
	{
		float time = con.getTime();
		clearFramebuffer(screen);

		int loc = 0, tslot = 0;
		int loc1 = 0;

		glm::mat4 model = glm::translate(glm::vec3(1, 0, 0));
		glm::mat4 model2 = glm::translate(glm::vec3(0, 0, 0));

		setFlags(RenderFlag::DEPTH);

		setUniforms(MyManager.getShader("shader1"), loc, tslot, cam_proj, cam_view,model, MyManager.getTexture("soulspear_normal"));
		s0_draw(screen, MyManager.getShader("shader1"), MyManager.getModel("soulspear"));

		setUniforms(MyManager.getShader("shader1"), loc1, tslot, cam_proj, cam_view, model2, MyManager.getTexture("soulspear_normal"));
		s0_draw(screen, MyManager.getShader("shader1"), MyManager.getModel("soulspear"));

		
	}


}