#include "model.h"

namespace Nata
{
	Model::Model(string path)
	{
		Load(path);
	}

	void Model::Draw(Shader shader)
	{
		for (unsigned int i = 0; i < Meshes.size(); i++)
		{
			Meshes[i].Draw(shader);
		}
	}

	void Model::Load(string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Meshes.push_back(this->ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		// process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3 vector3; // placeholder vec3
			vec2 vector2; // placeholder vec2

			// Position
			vector3.x = mesh->mVertices[i].x;
			vector3.y = mesh->mVertices[i].y;
			vector3.z = mesh->mVertices[i].z;
			vertex.Position = vector3;

			// Normal
			vector3.x = mesh->mNormals[i].x;
			vector3.y = mesh->mNormals[i].y;
			vector3.z = mesh->mNormals[i].z;
			vertex.Normal = vector3;

			// TexCoords
			if (mesh->mTextureCoords[0])
			{
				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vector2;
			}
			else
			{
				vertex.TexCoords = vec2(0.f);
			}

			if (mesh->HasTangentsAndBitangents())
			{
				// Tangent
				vector3.x = mesh->mTangents[i].x;
				vector3.y = mesh->mTangents[i].y;
				vector3.z = mesh->mTangents[i].z;
				vertex.Tangent = vector3;

				// Bitangent
				vector3.x = mesh->mBitangents[i].x;
				vector3.y = mesh->mBitangents[i].y;
				vector3.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector3;
			}
			else
			{
				vertex.Tangent = vec3(0.f);
				vertex.Bitangent = vec3(0.f);
			}

			vertices.push_back(vertex);
		}

		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// process materials
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// Assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN

			vector<Texture> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			// Specular maps
			vector<Texture> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		this->VertexCount = vertices.size();
		this->TrisCount = indices.size() / 3;

		return Mesh(vertices, indices, textures);
	}
	vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			bool skip = false;
			for (unsigned int j = 0; j < TexturesLoaded.size(); j++)
			{
				if (strcmp(TexturesLoaded[j].Path.data(), str.C_Str()) == 0)
				{
					textures.push_back(TexturesLoaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				// if textures hasnt been loaded already, load it
				Texture texture(str.C_Str(), Directory, typeName);
				textures.push_back(texture);
				TexturesLoaded.push_back(texture);
			}
		}
		return textures;
	}
}