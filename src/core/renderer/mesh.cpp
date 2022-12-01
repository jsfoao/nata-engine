#include "mesh.h"

namespace Nata
{
	NMesh::NMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<NTexture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		m_VAO = new VAO();
		m_VBO = new VBO(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
		m_IBO = new IBO(&this->indices[0], this->indices.size());

		this->SetupMesh();
	}

	NMesh::NMesh(vector<Vertex> vertices, vector<NTexture> textures)
	{
		this->vertices = vertices;
		this->textures = textures;

		m_VAO = new VAO();
		m_VBO = new VBO(&this->vertices[0], this->vertices.size() * sizeof(Vertex));

		this->SetupMesh();
	}

	NMesh::NMesh(vector<float> vertices, vector<NTexture> textures)
	{
		this->vertices = ToVertexData(vertices);
		this->textures = textures;

		m_VAO = new VAO();
		m_VBO = new VBO(&this->vertices[0], this->vertices.size() * sizeof(Vertex));

		this->SetupMesh();
	}

	void NMesh::BindResources()
	{
		if (this->textures.size() == 0)
			return;

		Shader->Enable();

		unsigned int diffuseNr = 0;
		unsigned int specularNr = 0;
		for (unsigned int i = 0; i < this->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			string number;
			string name = this->textures[i].Type;
			if (name == TEXTURE_DIFFUSE)
			{
				number = to_string(diffuseNr);
				diffuseNr++;
			}
			else if (name == TEXTURE_SPECULAR)
			{
				number = to_string(specularNr);
				specularNr++;
			}
			else
			{
				continue;
			}
			Shader->SetUniform1i((name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, this->textures[i].m_ID);
		}
	}

	void NMesh::Draw()
	{
		Shader->Enable();
		BindResources();
		mat4 model = mat4(1.f);
		model = translate(model, Position);
		model = scale(model, Scale);
		model = rotate(model, radians(Rotation.x), vec3(1.f, 0.f, 0.f));
		model = rotate(model, radians(Rotation.y), vec3(0.f, 1.f, 0.f));
		model = rotate(model, radians(Rotation.z), vec3(0.f, 0.f, 1.f));
		Shader->SetUniformMat4("model", model);

		m_VAO->Bind();
		m_IBO->Bind();
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		m_VAO->Unbind();
		m_IBO->Unbind();
	}

	void NMesh::DrawArrays()
	{
		Shader->Enable();
		BindResources();
		m_VAO->Bind();

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		m_VAO->Unbind();
		
		Shader->Disable();
	}

	void NMesh::SetupMesh()
	{
		m_VAO->Bind();
		m_VBO->Bind();
		VAOAttribLayout layout;
		layout.Push<float>(3); // Vertex position
		layout.Push<float>(3); // Vertex normals
		layout.Push<float>(2); // Vertex texture coords
		layout.Push<float>(3); // Vertex tangent
		layout.Push<float>(3); // Vertex bitangent
		m_VAO->AddBuffer(*m_VBO, layout);
		m_VBO->Unbind();
		m_VAO->Unbind();
	}

	vector<Vertex> NMesh::ToVertexData(const vector<float> vertices)
	{
		vector<Vertex> output;
		for (unsigned int i = 0; i < vertices.size(); i+=14)
		{
			vec3 vector3;
			vec2 vector2;
			Vertex vertex;

			// Position
			vector3.x = vertices[i];
			vector3.y = vertices[i+1];
			vector3.z = vertices[i+2];
			vertex.Position = vector3;

			// Normal
			vector3.x = vertices[i+3];
			vector3.y = vertices[i+4];
			vector3.z = vertices[i+5];
			vertex.Normal = vector3;

			// TexCoords
			vector2.x = vertices[i+6];
			vector2.y = vertices[i+7];
			vertex.TexCoords = vector2;

			// Tangent
			vector3.x = vertices[i+8];
			vector3.y = vertices[i+9];
			vector3.z = vertices[i+10];
			vertex.Tangent = vector3;

			// Bitangent
			vector3.x = vertices[i+11];
			vector3.y = vertices[i+12];
			vector3.z = vertices[i+13];
			vertex.Bitangent = vector3;

			output.push_back(vertex);
		}

		return output;
	}
}