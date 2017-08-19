#pragma once
#include "glm\\glm.hpp"

struct Vertex;

struct Geometry
{
	unsigned handle, //Vertex array object
			 vbo,	 //Vertex buffer
			 ibo,	 //Index buffer
			 size;   //How many indices make up this model
};

Geometry makeGeometry(const Vertex *verts, size_t vsize, 
					 const unsigned *idxs, size_t isize);


void freeGeometry(Geometry &g);

struct Shader
{
	unsigned handle; 
};

Shader makeShader(const char *vert_source, const char *frag_source);

void freeShader(Shader &s);

struct Framebuffer
{
	unsigned handle, width, height;

};

struct Texture
{
	unsigned handle;
};

//RGBA = 4 channels
// 512x512 image = 262144 pixels * 4 channells = ~ one million bytes

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);

void freeTexture(Texture &t);

