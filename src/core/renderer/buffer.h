#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

using namespace std;

namespace Nata
{
	class Buffer
	{
	public:
		Buffer(){ m_ID = 0; };

		~Buffer(){};
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

	protected:
		unsigned int m_ID;
	};

	class VBO : Buffer
	{
	public:
		VBO(const void* data, unsigned int size);

		void Bind();
		void Unbind();
		unsigned int GetID() const { return m_ID; };
	};

	class IBO : Buffer
	{
	public:
		IBO(const unsigned int* data, const unsigned int count);

		void Bind();
		void Unbind();
	};

	struct VAOAttribElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalised;

		VAOAttribElement(unsigned int type, unsigned int count, unsigned char normalised) :
			type(type), count(count), normalised(normalised) {}

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
				case GL_FLOAT : return 4;
				case GL_UNSIGNED_INT : return 4;
				case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};

	class VAOAttribLayout
	{
	public:
		vector<VAOAttribElement> Elements;
		unsigned int Stride;

		VAOAttribLayout() : Stride(0) {}

		template<typename T>
		void Push(unsigned int count) {}

		template<>
		void Push<float>(unsigned int count) 
		{
			Elements.push_back(VAOAttribElement(GL_FLOAT, count, GL_FALSE));
			Stride += VAOAttribElement::GetSizeOfType(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			Elements.push_back(VAOAttribElement(GL_UNSIGNED_INT, count, GL_FALSE));
			Stride += VAOAttribElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			Elements.push_back(VAOAttribElement(GL_UNSIGNED_BYTE, count, GL_FALSE));
			Stride += VAOAttribElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
		}
	};

	class VAO
	{
	public:
		VAO();
		~VAO();

		void Bind();
		void Unbind();

		void AddBuffer(VBO& vbo, const VAOAttribLayout& layout);

	protected:
		unsigned int m_ID;
	};
}