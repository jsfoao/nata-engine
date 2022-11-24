#pragma once
#include "core/glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"
#include "mesh.h"

#include "assimp/config.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
namespace Nata
{
	class Model
	{
	public:
		vector<Mesh> Meshes;
		string Directory;
		vector<Texture> TexturesLoaded;

		unsigned int VertexCount;
		unsigned int TrisCount;

		Model(string path);
		void Draw(Shader shader);
		void AddTexture(Texture texture)
		{
			for (unsigned int i = 0; i < Meshes.size(); i++)
			{
				Meshes[i].AddTexture(texture);
			}
		}

		void Load(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}
