#version 450 core
//// enable for bindless textures
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_gpu_shader_int64 : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 v_textPos;

out vec2 u_textPos;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position =  projection * model * vec4(position, 1.0);
	u_textPos = v_textPos;
}