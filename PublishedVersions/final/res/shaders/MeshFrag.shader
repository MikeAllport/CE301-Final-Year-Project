#version 450 core
// enable for bindless textures
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_gpu_shader_int64 : enable

layout(location = 0) out vec4 color;
in vec2 u_textPos;

layout(bindless_sampler) uniform sampler2D textHandle;
uniform sampler2D text;

void main()
{
	color = texture(text, u_textPos);
}