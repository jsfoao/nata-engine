#pragma once
#include "core/glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"
#include "buffer.h"

#define N_DRAW_ELEMENTS 0
#define N_DRAW_ARRAYS 1
#define N_DRAW_LINES 2

using namespace std;

namespace Nata
{
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoords;
		vec3 Tangent;
		vec3 Bitangent;
	};

	class Mesh
	{
	public:
		//mesh data
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

	public:
		VAO* m_VAO;
		VBO* m_VBO;
		IBO* m_IBO;

	public:

		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		Mesh(vector<Vertex> vertices, vector<Texture> textures);
		Mesh(vector<float> vertices, vector<Texture> textures);

		void BindResources(Shader shader);
		void Draw(Shader shader);
		void DrawArrays(Shader shader);
		void AddTexture(Texture texture)
		{
			textures.push_back(texture);
		}
		

	private:
		void SetupMesh();

	public:
		static vector<Vertex> ToVertexData(const vector<float> vertices);
	};
}