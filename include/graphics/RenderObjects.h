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

void solveTangents(Vertex *v, size_t vsize,
	const unsigned *idxs, size_t isize);

struct Shader
{
	unsigned handle; 
};

Shader makeShader(const char *vert_source, const char *frag_source);

void freeShader(Shader &s);

struct Texture
{
	unsigned handle;
};

struct Framebuffer
{
	unsigned handle;
	unsigned width, height;
	unsigned nTargets;
	

	Texture depthTarget;
	Texture targets[8];

};



//RGBA = 4 channels
// 512x512 image = 262144 pixels * 4 channells = ~ one million bytes

Texture makeTexture(unsigned w, unsigned h, unsigned c, const void * pixels, bool isFloat = false);

void freeTexture(Texture &t);

Framebuffer MakeFrameBuffer(unsigned w, unsigned h, unsigned c, bool hasDepth, unsigned nTargets, unsigned nFloatTargets);

void freeFrameBuffer(Framebuffer & fb);

