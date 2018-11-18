#version 430

in vec3 LightIntensity;

out vec4 FragColor;

void main(){
	vec3 color;
	color.x= LightIntensity.x + 0.2f;
	color.y = LightIntensity.y + 0.2f;
	color.z = LightIntensity.z;

	FragColor = vec4(color,1.0);
}