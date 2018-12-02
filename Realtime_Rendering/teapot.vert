#version 430

layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

//out vec3 LightIntensity;
out vec4 Position;
out vec3 Normal;



uniform mat4 MVP;

void main(){
	Position = VertexPosition;
	Normal = VertexNormal;

	gl_Position = MVP * VertexPosition;

}