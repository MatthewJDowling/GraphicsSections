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
