#version 430

in vec4 Position;
in vec3 Normal;
out vec4 FragColor;


uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
//uniform float Shininess;

vec4 LightLocation = {50.0f,50.0f,50.0f,1.0f};



uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;

void main(){
	vec3 Ia,Is;
	vec3 Id = {1.0f,1.0f,1.0f};
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




	FragColor = vec4(color,0.5f);
}