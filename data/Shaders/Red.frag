#version 460
layout(location = 0) in vec3 pos; 
layout(location = 1) in vec3 normal; 
layout(location = 2) in vec2 texture_coords; 
uniform sampler2D u_texture_diffuse1;

layout(location = 0) out vec4 frag_color; 

void main() { 
	frag_color = vec4(1.0, 0.0, 0.0, 0.0);//texture(u_texture_diffuse1, texture_coords);
};