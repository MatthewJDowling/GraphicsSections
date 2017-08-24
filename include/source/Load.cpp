#include <fstream>
#include <string>
#include "graphics\Vertex.h"
#include "graphics\Load.h"
#include "graphics\RenderObjects.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

Texture loadTexture(const char *path)
{
	Texture retval = { 0 };

	int w, h, c;

	unsigned char *pixels;

	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	retval = makeTexture(w, h, c, pixels);

	stbi_image_free(pixels);

	return retval; 

}

Shader loadShader(const char * vpath, const char * fpath)
{
	Shader retval = { 0 };

	const char *vsource;
	const char *fsource;

	std::ifstream infile { fpath };
	std::string frag_contents{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };

	fsource = frag_contents.c_str();

	std::ifstream infile2 { vpath }; 
	std::string vert_contents{ std::istreambuf_iterator<char>(infile2), std::istreambuf_iterator<char>() };

	vsource = vert_contents.c_str();
		

	retval = makeShader(vsource, fsource);

	return retval; 
}

Geometry loadGeometry(const char *path)
{
	Geometry retval = { 0,0,0,0 };
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;


	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	size_t vsize = attrib.vertices.size() / 3;
	Vertex* verts = new Vertex[vsize];

	for (size_t i = 0; i < vsize; i++)
	{
		const float *p = &attrib.vertices[i * 3];
		verts[i].position = {p[0], p[1], p[2],1};
	}

	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];
	
	for (size_t i = 0; i < isize; ++i)
	{
		indices[i] = shapes[0].mesh.indices[0].vertex_index;
	}


	retval = makeGeometry(verts,vsize,indices,isize);

	delete[] verts;
	delete[] indices;

	return retval;
}