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

 	size_t isize = shapes[0].mesh.indices.size();
	size_t *indicies = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (size_t i = 0; i < isize; i++)
	{
		indicies[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;

		const float *p = &attrib.vertices [pi * 3];
		const float *n = &attrib.normals  [ni * 3];
		const float *t = &attrib.texcoords[ti * 2];

		verts[i].position		   = {p[0],p[1],p[2],1};
		verts[i].textureCoordinate = {t[0],t[1]};
		verts[i].normal			   = { n[0],n[1],n[2],0 };
	}



	solveTangents(verts, vsize, indicies, isize);

	retval = makeGeometry(verts,vsize,indicies,isize);

	delete[] verts;
	delete[] indicies;

	return retval;
}