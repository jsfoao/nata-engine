#pragma once
#include <vector>
#include "core/glm_math.h"
#include "texture.h"
#include "shader.h"
#include "buffer.h"
#include "renderable.h"

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

	class NMesh : public NRenderable
	{
	public:
		//mesh data
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<NTexture> textures;

		bool DrawArrays;
		int DrawMode;

	public:
		VAO* m_VAO;
		VBO* m_VBO;
		IBO* m_IBO;

	public:

		NMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<NTexture> textures, bool drawArrays = false, int drawMode = GL_TRIANGLES);
		NMesh(vector<Vertex> vertices, vector<NTexture> textures, bool drawArrays = false, int drawMode = GL_TRIANGLES);
		NMesh(vector<float> vertices, vector<NTexture> textures, bool drawArrays = false, int drawMode = GL_TRIANGLES);
		NMesh(vector<float> vertices, bool drawArrays = false, int drawMode = GL_TRIANGLES);

		void BindResources();
		void Draw() override;
		// GL_TRIANGLES, GL_LINES
		void DrawArr();
		void AddTexture(NTexture texture)
		{
			textures.push_back(texture);
		}

		void SetVAO(VAO* vao)
		{
			m_VAO = vao;
		}
		void SetVBO(VBO* vbo)
		{
			m_VBO = vbo;
		}
		void SetIBO(IBO* ibo)
		{
			m_IBO = ibo;
		}
		

	private:
		void SetupMesh();

	public:
		static vector<Vertex> ToVertexData(const vector<float> vertices);
	};
}