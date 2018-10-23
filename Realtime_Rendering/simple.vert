
#version 450
/*
1.Create shader object
2.Specify shader file names
3.Setup a VAO(Vertex Array Object) VAO�� �����̳�, �������� ���� �׸����� �ϴ� obj��
	full description�� �����ִ� �����̳�.

4.Setup VBOs (Vertex Buffer Object) VBO�� object�� Attribute(�Ӽ�)�� �����ϱ����� ����
vbo�� �ΰ� �����. ��ġ �׸��� ����.

5.Close the VAO

6.Setup the transformation matrices
7.Draw
*/
//vertex ---(in)--> v.s. -> assembly
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

out vec3 fColor;


void main(){
	
//	mat4 model;
//	mat4 view;
//	mat4 projection;

//	vet4 ndc = projection * view * model * Position;

	fColor = Color;
	vec4 ndc = vec4(Position,1.0f);
	gl_Position = ndc;		// �����׸�Ʈ�� ������ ������ �����ؼ� ����
	

	//gl_Position = ??			// NDC(-1~1 ���� ���ԵǴ� ��ǥ�� )��ǥ���� �����ϴ� in-built�Լ�
}
//local -> global -> comcu - clip -> ndc(���������� �ؾ��ϴ� ��)