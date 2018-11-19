#version 430

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 color;

out vec3 fColor;

uniform mat4 MVP;

void main(){
	fColor = color;
	gl_Position = MVP * vertex;
		
}
