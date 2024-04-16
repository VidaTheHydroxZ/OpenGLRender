#pragma once

#include <vector>
#include <GL/glew.h>
#include <stdexcept>

#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {}

	
	void Push (unsigned int type, unsigned int count)
	{
		if (type == GL_FLOAT)
		{
			m_Elements.push_back({ type, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}
		else if (type == GL_UNSIGNED_INT)
		{
			m_Elements.push_back({ type, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}
		else if (type == GL_UNSIGNED_BYTE)
		{
			m_Elements.push_back({ type, count, GL_TRUE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

