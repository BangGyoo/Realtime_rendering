#version 430

in vec4 Position;
in vec3 Normal;
out vec4 FragColor;


uniform vec4 LightLocation;
uniform vec3 Kd;
uniform vec3 Id;

const vec3 Ka = vec3(0.0,0.0,0.0);
const vec3 Ks = vec3(0.5,0.5,0.5);

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;

void main(){
	vec3 Ia,Is;
	Ia = Is = Id;

	vec3 N = normalize( NormalMatrix * Normal);
	vec4 P = ModelViewMatrix * Position;
	vec3 L = normalize((LightLocation - P).xyz);
	vec3 V = normalize(-P.xyz);
	vec3 R = normalize(reflect(-L,N));
	vec3 diffuse = Kd * Id * max(dot(N,L),0.0f);
	vec3 ambient = Ka * Ia;
	vec3 specular = Ks * Is * pow(max(dot(R,V),0.0),32.0);
	
	vec3 color = (diffuse + ambient + specular);
	
	FragColor = vec4(color,1.0f);
}