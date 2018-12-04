
#version 430

//layout (location = ��Ʈ����Ʈ ��ȣ) //in: input�� �ǹ�. ���ؽ����̴��� input�� �ݵ�� ���ø����̼����κ��� ����
in vec4 vertexPosition; //ù ��° VBO
in vec4 vertexTexture; //�� ��° VBO
in vec3 vertexNormal; //�� ��° VBO //layout (location = 1) in vec3 vertexColor;

out vec4 Position;
out vec3 Normal;

uniform mat4 ModelViewMatrix; //view * model ���
uniform mat3 NormalMatrix; //normal ���
uniform mat4 mvp; //mvp = projection * view * model

void main() //main()���� �� ���� uniform ������ ������!
{
	Position =  ModelViewMatrix * vertexPosition; //P //local -> camera ��ǥ�� ��ȯ
	Normal = normalize(NormalMatrix * vertexNormal); //N

	gl_Position = mvp * vertexPosition;
}
