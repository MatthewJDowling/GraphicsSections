#pragma once

#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include "RenderObjects.h"


struct Camera
{
	glm::mat4 view;
	glm::mat4 proj;
};

struct SpecGloss
{
	Geometry geo;
	std::string objName;
	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;
	
	float gloss;
};

void createAllAssets(SpecGloss objects[], int size);


struct StandardLight
{
	glm::vec3 dir;
	glm::vec4 color;
	
	float intensity;
	glm::vec4 ambient;

	int type;
};

struct Dlite
{
	glm::vec3 target;
	float range; 

	glm::vec3 direction; 
	

	glm::mat4 getProj() const 
	{
		return glm::ortho<float>(-range, range, -range, range, -range, range);
	}
	glm::mat4 getView() const 
	{
		return glm::lookAt(-direction + target, target, glm::vec3(0, 1, 0));
	}

	glm::vec4 color; 
	float intensity; 
};


namespace __internal
{
	void t_setUniform(const Shader &s, int & loc_io, int & tex_io, const Camera & val);
	
	void t_setUniform(const Shader &s, int & loc_io, int &tex_io, const SpecGloss & val);

	void t_setUniform(const Shader &s, int & loc_io, int &tex_io, const Dlite & val);


}


