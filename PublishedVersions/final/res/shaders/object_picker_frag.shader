#version 450 core

layout(location = 0) out vec4 color;
//in vec3 v_textCoord;
in vec4 u_col;
in vec2 u_textPos;
in flat float u_textSlot;

uniform float time;
uniform sampler2D textures[32];

void main()
{
	vec4 testColor = texture(textures[int(u_textSlot)], u_textPos);
	color = vec4(u_col[0], u_col[1], u_col[2], testColor[3]);
}