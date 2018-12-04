
#version 430

in vec4 Position;
in vec3 Normal;

struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 Ia;       // Ambient light intensity
  vec3 Id;       // Diffuse light intensity
  vec3 Is;       // Specular light intensity
};

uniform LightInfo Light;

struct MaterialInfo {
  vec3 Ka;          // Ambient reflectivity
  vec3 Kd;          // Diffuse reflectivity
  vec3 Ks;          // Specular reflectivity
  float Shiness;    // Specular shininess factor (phong exponent)
};

uniform MaterialInfo Material;

out vec4 FragColor;

void main()
{ //여태까지 한 건 Position Light인데 D 무시하고 계산하고 있었음.
	vec3 L = normalize((Light.Position - Position).xyz); //광원 벡터
	vec3 V = normalize(-Position.xyz); //V = (0,0,0)-P = -P
	vec3 R = normalize(reflect(-L,Normal)); //Phong
	//vec3 H = normalize(V + L); //Blinn-Phong

	vec3 ambient = Light.Ia * Material.Ka;
	vec3 diffuse = Light.Id * Material.Kd * max(dot(Normal,L),0.0);
	vec3 specular = Light.Is * Material.Ks * pow(max(dot(R,V),0.0),Material.Shiness); //Phong
	//vec3 specular = Light.Is * Material.Ks * pow(max(dot(H,V),0.0),Material.Shiness); //Blinn-Phong
	//spec 계산할 때 Ks가 아닌 Is만 곱하는 경우도 있음

	vec3 LightIntensity = ambient + diffuse + specular;
	
	FragColor = vec4(LightIntensity,1.0);
}