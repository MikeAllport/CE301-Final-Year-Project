#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_col;
layout(location = 2) in vec2 v_textPos;

out vec3 u_col;
out vec2 textPos;

// TODO: replace functionality with own math matrix, or glOrtho
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out float uniTime;

layout(std140, binding = 0) buffer Buffer
{
	mat4 projection;
	mat4 model;
	mat4 view;
	float time;
} infoBuffer;

void main()
{
	// isometric coordinate conversion
	//vec4 position2;
	//position2.x = position.x - position.y;
	//position2.y = (position.x + position.y) / 2;
	//position2.z = position.z;
	//position2.w = position.w;
	//gl_Position = u_Projection * position2 ;

	gl_Position = infoBuffer.projection * infoBuffer.model * infoBuffer.view * vec4(position, 1.0f);
	u_col = v_col;
	textPos = v_textPos;
}