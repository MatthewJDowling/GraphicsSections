#pragma once


#include "glm\glm.hpp"
struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;
void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);

void clearFramebuffer(const Framebuffer &F, bool color = true,  bool depth = true);


enum RenderFlag { DEPTH = 1 };

void setFlags(int flags);

void setUniform(const Shader &s, int location, float value);
void setUniform(const Shader &s, int location, int value);
void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);


void setUniform(const Shader &s, int location, glm::mat4 val);

//These will be called each time the variadic unpacking recursion takes place
//Based upon what uniforms are passed in, the correct function will automatically 
// be called. 
namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);


	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);
}

//the recursive template function.
// U is a variadic template parameter. Each time the function is called
// the T parameter will consume 1 element of the variadic.

template <typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&... uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);

	setUniforms(s, loc_io, tex_io, uniforms...);
}
//Base Case
template <typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
}

