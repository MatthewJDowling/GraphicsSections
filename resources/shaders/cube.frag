#version 450

in vec4 vCol;

in vec4 vNormal;
in vec2 vUV;

layout(location = 1) uniform sampler2D map;

out vec4 outColor;

void main()
{
	outColor = dot(vNormal, -normalize(vec4(1,0,1,0))) * texture(map, vUV);

	//outColor = vec4(1,1,0,1);
}