#include "Object.h"


std::vector<glm::vec4> obj_vertices;
std::vector<glm::vec3> obj_colors;
GLushort *obj_elements;

int Object::loadObj() {
	int size = 0;		// return 값

	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, true);
	unsigned flags =
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_GenNormals;



	const aiScene* scene = importer.ReadFile(path, flags);
	if (!scene) return -1;

	const aiMesh* mesh = scene->mMeshes[0];

	uint32_t numFaces = 0;

	numFaces = mesh->mNumFaces;

	obj_elements = new GLushort[3 * mesh->mNumFaces];

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

		obj_elements[3 * i] = mesh->mFaces[i].mIndices[0];
		obj_elements[3 * i + 1] = mesh->mFaces[i].mIndices[1];
		obj_elements[3 * i + 2] = mesh->mFaces[i].mIndices[2];

	}
	size = mesh->mNumFaces;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

		aiVector3D tmp = mesh->mVertices[obj_elements[i]];
		obj_vertices.push_back(glm::vec4(tmp.x - 3, tmp.y, tmp.z - 3, 1.0f));
	}
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		obj_colors.push_back(glm::vec3(0.8f, 0.8f, 0.6f));
	}
	return size;
}

void Object::setup()  //Call from constructor
{

	int size = loadObj();

	glGenVertexArrays(1, &vaoHandle);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vaoHandle);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
	//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다
	//vbo 생성
	glGenBuffers(1, &vbo_obj_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_obj_vertices);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* obj_vertices.size() * 4, obj_vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib 번호 (0,1,....)
		4,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,//sizeof(float),					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(0);			// vbo 종료
												// 이 함수 쓰면 GPU에서 잡히게 된다. 한번 넣어주면 변하지x
												// 어지간한 것들은 static 써도 무방
	glGenBuffers(1, &vbo_obj_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_obj_colors);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* obj_vertices.size() * 3, obj_colors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0				// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(1);			// vbo 종료

	glGenBuffers(1, &ibo_obj_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_obj_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)size * 3, obj_elements, GL_STATIC_DRAW);
	
	glBindVertexArray(0);		// vao종료, 해당 함수에 0을 넣으면 종료 unbind 된다.
	

	delete obj_elements;

}

void Object::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

}

