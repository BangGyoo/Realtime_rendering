#version 430
layout (location = 0) in vec4 Position;
layout (location = 1) in vec3 Color;

uniform mat4 mvp;

out vec3 fColor;


void main(){

	fColor = Color; 
	gl_Position = mvp * Position;
}