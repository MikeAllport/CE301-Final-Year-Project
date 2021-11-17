#version 450 core

layout(location = 0) out vec4 color;
//in vec3 v_textCoord;
in vec4 u_col;
in vec2 u_textPos;
in flat float u_textSlot;

uniform float time;
uniform sampler2D textures[32];
uniform vec3 stencil_col;

void main()
{
	vec4 actualColor = texture(textures[int(u_textSlot)], u_textPos);
	color = vec4(vec3(actualColor[0], actualColor[1], actualColor[2]) * stencil_col, actualColor[3]);
}