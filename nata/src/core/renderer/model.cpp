#include "model.h"

namespace Nata
{
	NModel::NModel(string path) 
	{
		m_OrigPath = path;
	}

	void NModel::Draw()
	{
		for (unsigned int i = 0; i < Meshes.size(); i++)
		{
			Meshes[i].Position = Position;
			Meshes[i].Scale = Scale;
			Meshes[i].Rotation = Rotation;
			Meshes[i].Shader = Shader;
			Meshes[i].Draw();
		}
	}

	bool NModel::Load()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_OrigPath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return false;
		}

		ProcessNode(scene->mRootNode, scene);
		return true;
	}

	void NModel::ProcessNode(aiNode* node, const aiScene* scene)
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

	NMesh NModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<NTexture> textures;

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

			vector<NTexture> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			// Specular maps
			vector<NTexture> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		this->VertexCount = vertices.size();
		this->TrisCount = indices.size() / 3;

		return NMesh(vertices, indices, textures);
	}
	vector<NTexture> NModel::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<NTexture> textures;
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
				NTexture texture(str.C_Str(), Directory, typeName);
				textures.push_back(texture);
				TexturesLoaded.push_back(texture);
			}
		}
		return textures;
	}
	bool NModel::Create(std::string path, std::string dest, std::string name)
	{
		NModel* model = new NModel(path);
		model->m_OrigPath = path;
		model->m_Path = dest;
		model->m_Name = name;
		model->m_Type = AssetType::Model;
		bool valid = model->Load();
		if (!valid)
		{
			std::string message = "NMODEL::CREATE : Failed to create asset " + name;
			std::cout << message << std::endl;
			return false;
		}
		NAsset::Submit(model);
		return true;
	}
}