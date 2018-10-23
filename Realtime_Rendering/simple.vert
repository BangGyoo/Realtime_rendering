
#version 450
/*
1.Create shader object
2.Specify shader file names
3.Setup a VAO(Vertex Array Object) VAO는 컨테이너, 저장위한 공간 그리고자 하는 obj의
	full description을 갖고있는 컨테이너.

4.Setup VBOs (Vertex Buffer Object) VBO는 object의 Attribute(속성)을 저장하기위한 버퍼
vbo는 두개 만든다. 위치 그리고 색깔.

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
	gl_Position = ndc;		// 프래그먼트의 꼭지점 색상을 결정해서 보냄
	

	//gl_Position = ??			// NDC(-1~1 까지 포함되는 좌표계 )좌표값이 들어야하는 in-built함수
}
//local -> global -> comcu - clip -> ndc(최종적으로 해야하는 것)