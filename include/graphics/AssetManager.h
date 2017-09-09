#pragma once
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include <string>


#include "GameObjects.h"

struct Asset
{
	Geometry geo;

	glm::mat4 model;
	Texture diffuse;
	Texture specular;
	Texture normal;

	std::string name; 
};

Asset createAsset(Geometry assetGeo, Texture assetDiffuse, Texture assetSpecular, Texture assetNormal, std::string assetName);

