#pragma once
#include <map>
#include <string>
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "RenderObjects.h"

class AssMan
{
	static std::map<std::string, Geometry> geoMap;
	static std::map<std::string, Texture> texMap;
	static std::map<std::string, Shader> shdMap;

public:
	static std::string fallbackModel;

	static bool loadModelAsset(const char * name, const char * filePath);
	static bool loadTextureAsset(const char * name, const char * filePath);
	static bool loadShaderAsset(const char * name, const char * VfilePath, const char * FfilePath);

	static Geometry& getModel(const char * name);
	static Texture& getTexture(const char * name);
	static Shader& getShader(const char * name);
};