
#version 430

//layout (location = 애트리뷰트 번호) //in: input을 의미. 버텍스쉐이더의 input은 반드시 어플리케이션으로부터 받음
in vec4 vertexPosition; //첫 번째 VBO
in vec4 vertexTexture; //두 번째 VBO
in vec3 vertexNormal; //세 번째 VBO //layout (location = 1) in vec3 vertexColor;

out vec4 Position;
out vec3 Normal;

uniform mat4 ModelViewMatrix; //view * model 행렬
uniform mat3 NormalMatrix; //normal 행렬
uniform mat4 mvp; //mvp = projection * view * model

void main() //main()에서 안 쓰는 uniform 있으면 에러남!
{
	Position =  ModelViewMatrix * vertexPosition; //P //local -> camera 좌표계 변환
	Normal = normalize(NormalMatrix * vertexNormal); //N

	gl_Position = mvp * vertexPosition;
}
