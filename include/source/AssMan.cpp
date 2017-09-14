#include "graphics\Load.h"
#include "..\include\\graphics\AssMan.h"

std::map<std::string, Geometry> AssMan::geoMap;
std::map<std::string, Texture> AssMan::texMap;
std::map<std::string, Shader> AssMan::shdMap;
std::string AssMan::fallbackModel;

bool AssMan::loadModelAsset(const char * name, const char * filePath)
{
	AssMan::geoMap[name] = loadGeometry(filePath);

	return true;
}

bool AssMan::loadTextureAsset(const char * name, const char * filePath)
{
	AssMan::texMap[name] = loadTexture(filePath);

	return true;
}

bool AssMan::loadShaderAsset(const char * name, const char * VfilePath, const char * FfilePath)
{
	AssMan::shdMap[name] = loadShader(VfilePath, FfilePath);

	return true;
}

Geometry & AssMan::getModel(const char * name)
{

	return AssMan::geoMap[name];
}

Texture & AssMan::getTexture(const char * name)
{
	return AssMan::texMap[name];
}

Shader & AssMan::getShader(const char * name)
{
	return AssMan::shdMap[name];
}
