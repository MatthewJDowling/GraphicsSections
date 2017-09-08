#include "..\include\graphics\GameObjects.h"
#include "graphics\draw.h"


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
