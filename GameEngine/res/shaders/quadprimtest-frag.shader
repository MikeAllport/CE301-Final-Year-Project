#version 450 core
// enable for bindless textures
//#extension GL_ARB_bindless_texture : enable
//#extension GL_ARB_gpu_shader_int64 : enable

layout(location = 0) out vec4 color;
//in vec3 v_textCoord;
in vec4 u_col;
in vec2 u_textPos;
in float u_textSlot;

uniform float time;
uniform sampler2D textures[32];

// for bindless
//uniform uint64_t u_textHandle;

void main()
{
	if (u_textSlot == -1.0)
	{
		float timeSin = (sin(time * 10) / 2f) + 1.0f;
		vec4 color1 = vec4(u_col.x * timeSin, u_col.y * timeSin, u_col.z * timeSin, 1.0);
		color = color1;
	}
	else
	{
		color = texture(textures[int(u_textSlot)], u_textPos);
		// for bindless textures
		//sampler2D textSampler = sampler2D(u_textHandle); 
		//color = texture(textSampler, u_textPos);
	}
}