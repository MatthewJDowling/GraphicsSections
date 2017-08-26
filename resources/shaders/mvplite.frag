#version 450

in vec2 vUV;

layout(location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{

	//outColor = vec4(1,1,0,1);

	outColor = texture(diffuse, vUV);
}