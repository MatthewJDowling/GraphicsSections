#include "..\include\graphics\GameObjects.h"
#include "graphics\draw.h"
#include "graphics\Load.h"

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Camera & val)
{
	t_setUniform(s, loc_io, tex_io, val.proj); // 0
	t_setUniform(s, loc_io, tex_io, val.view);
}

void __internal::t_setUniform(const Shader &s, int & loc_io, int &tex_io, const SpecGloss & val)
{
	t_setUniform(s, loc_io, tex_io, val.model);

	t_setUniform(s, loc_io, tex_io, val.diffuse);
	t_setUniform(s, loc_io, tex_io, val.specular);
	t_setUniform(s, loc_io, tex_io, val.normal);
	t_setUniform(s, loc_io, tex_io, val.gloss);
}

void __internal::t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Dlite & val)
{
	//
}



void createAllAssets(SpecGloss objects[], int size)
{
	//SoulSpear
	objects[0].objName = "SoulSpear";
	objects[0].geo = loadGeometry("../../resources/models/soulspear.obj");
	//objects[1].geo = "soulspear";
	objects[0].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	objects[0].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	objects[0].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	objects[0].gloss = 4.0f;


	objects[2] = objects[0];
	objects[2].objName = "GLOSSY AS FUCK SOUL SPEAR";
	objects[2].gloss = 24556;

	objects[1].geo = loadGeometry("../../resources/models/cube.obj");
	objects[1].diffuse = loadTexture("../../resources/textures/four_diffuse.tga");
	objects[1].specular = loadTexture("../../resources/textures/four specular.tga");
	objects[1].normal = loadTexture("../../resources/textures/four_normal.tga");
	objects[1].gloss = 4;


}