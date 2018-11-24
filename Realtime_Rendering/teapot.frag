#version 430

in vec3 LightIntensity;

out vec4 FragColor;

void main(){
	vec3 color;
	color.x= LightIntensity.x;
	color.y = LightIntensity.y ;
	color.z = LightIntensity.z;

	FragColor = vec4(color,1.0);
}