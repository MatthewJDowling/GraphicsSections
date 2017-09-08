#version 45

in vec2 vUV;

layout(location = 0) uniform mat4 view;

layout(location = 1) uniform mat4 lightView;

layout(location = 3) uniform vec4 lightColor;

layout(location = 4) uniform float intensity;

layout(location = 5) uniform sampler2D normalMap;

layout(location = 0) out vec4 outDiffuse;

void main()
{
	vec3 L = (view * lightView[2]).xyz;
	vec3 N = texture(normalMap, vUV).xyz;

	float lamb = max(0, dot(-L,N));

	outDiffuse = lightColor * intensity * lamb; 
}