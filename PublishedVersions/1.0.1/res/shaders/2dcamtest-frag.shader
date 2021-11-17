#version 450 core

layout(location = 0) out vec4 color;
//in vec3 v_textCoord;
in vec3 u_col;
in vec2 textPos;
in float uniTime;

uniform float time;
uniform sampler2D ourTexture;

layout(std140, binding = 0) buffer Buffer
{
	mat4 projection;
	mat4 model;
	mat4 view;
	float time;
} infoBuffer;

void main()
{
	float timeSin = (sin(infoBuffer.time *10) / 2f) + 1.0f;
	//vec4 textCol = texture(u_text, v_textCoord);
	//color1 = color;
	//u_col;
	vec4 color1 = vec4(u_col.x * timeSin, u_col.y * timeSin, u_col.z * timeSin, 1.0);
	color =  color1;
}