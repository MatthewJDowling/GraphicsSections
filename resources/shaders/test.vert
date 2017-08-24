//Graphics\resources\shaders\test.vert
		
#version 450
	

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

layout(location = 1) uniform int idx = 0; 
layout(location = 2) uniform int rows = 4;
layout(location = 3) uniform int cols =4;



out vec2 vUV;

void main () 
{

int r = idx / cols;
int c = idx % rows;


gl_Position = position; 
vUV = (vec2(r,c) + textCoord) / vec2(rows,cols);

}