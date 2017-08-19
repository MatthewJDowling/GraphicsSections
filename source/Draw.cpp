#include "glinc.h"
#include "graphics\Draw.h"
#include "graphics\RenderObjects.h"

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g)
{
	//what we are using 
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	//what area of the framebuffer do we draw to
	glViewport(0, 0, f.width, f.height);

	//draw the elements 
	glDrawElements(GL_TRIANGLES,g.size,GL_UNSIGNED_INT,0);

	//Unbind 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}

void clearFramebuffer(const Framebuffer &F)
{
	glBindFramebuffer(GL_FRAMEBUFFER, F.handle);

	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void setUniform(const Shader &s, int location, float value)
{

	glProgramUniform1f(s.handle, location, value);
}

void setUniform(const Shader & s, int location, int value)
{
	glProgramUniform1i(s.handle, location, value);
}

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle,location,slot);
}



