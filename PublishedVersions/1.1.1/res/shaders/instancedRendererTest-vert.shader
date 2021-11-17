#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in float samplerLoc;

out vec2 u_textPos;
out float u_textSlot;
out vec4 u_col;

// TODO: replace functionality with own math matrix, or glOrtho
uniform mat4 projection;

layout(std430, binding = 0) buffer Model
{
	mat4 model[];
} model;

layout(std430, binding = 1) buffer Color
{
	vec4 color[];
} color;

layout(std430, binding = 2) buffer TextSlot
{
	float textSlot[];
} textSlot;

layout(std430, binding = 3) buffer TextPosition
{
	vec2 textPos[][4];
} textPos;

void main()
{
	gl_Position = projection * model.model[gl_InstanceID] * vec4(position, 1.0f);
	u_textPos = textPos.textPos[gl_InstanceID][int(samplerLoc)];
	u_textSlot = textSlot.textSlot[gl_InstanceID];
	u_col = color.color[gl_InstanceID];
}