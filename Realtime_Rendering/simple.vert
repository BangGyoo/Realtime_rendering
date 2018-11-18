#version 430

layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightLocation;
uniform vec3 Kd;
uniform vec3 Id;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main(){
	vec3 N = normalize( NormalMatrix * VertexNormal);
	vec4 P = ModelViewMatrix * VertexPosition;
	vec3 L = normalize((LightLocation - P).xyz);
//	vec3 V = normalize(-P.xyz);
//	vec3 R = normalize(reflect(-L,N));

	vec3 diffuse = Kd * Id * max(dot(N,L),0.0f);
//	vec3 ambient = Ka * Ia;
//	vec3 specular = Ks * Is * pow(max(dot(R,V),100.0),0.0);

	LightIntensity = diffuse;
	gl_Position = MVP * VertexPosition;
}