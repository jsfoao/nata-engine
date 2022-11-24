#include "buffer.h"

namespace Nata
{
	VBO::VBO(const void* data, unsigned int size)
	{
		glGenBuffers(1, &m_ID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	IBO::IBO(const unsigned int* data, const unsigned int count)
	{
		glGenBuffers(1, &m_ID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		Unbind();
	}

	void IBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IBO::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VAO::VAO()
	{
		glGenVertexArrays(1, &m_ID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VAO::Bind()
	{
		glBindVertexArray(m_ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::AddBuffer(VBO& vbo, const VAOAttribLayout& layout)
	{
		Bind();
		vbo.Bind();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < layout.Elements.size(); i++)
		{
			VAOAttribElement el = layout.Elements[i];
			glVertexAttribPointer(i, el.count, el.type, el.normalised, layout.Stride, (void*)(size_t)offset);
			glEnableVertexAttribArray(i);
			offset += el.count * VAOAttribElement::GetSizeOfType(el.type);
		}
	}
}

