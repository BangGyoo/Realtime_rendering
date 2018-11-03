#version 430
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

uniform mat4 mvp;

out vec3 fColor;


void main(){

	fColor = Color;
	vec4 ndc = vec4(Position,1.0f);
	gl_Position = mvp * ndc;
}