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
	class NModel
	{
	public:
		vector<NMesh> Meshes;
		string Directory;
		vector<NTexture> TexturesLoaded;

		unsigned int VertexCount;
		unsigned int TrisCount;

		NModel(string path);
		void Draw(NShader shader);
		void AddTexture(NTexture texture)
		{
			for (unsigned int i = 0; i < Meshes.size(); i++)
			{
				Meshes[i].AddTexture(texture);
			}
		}

		void Load(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		NMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<NTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	};
}
