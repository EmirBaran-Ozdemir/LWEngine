#include "lwpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "glad/glad.h"


namespace LWEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case LWEngine::ShaderDataType::Float:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Float2:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Float3:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Float4:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Mat3:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Mat4:			return GL_FLOAT;
			case LWEngine::ShaderDataType::Int:				return GL_INT;
			case LWEngine::ShaderDataType::Int2:			return GL_INT;
			case LWEngine::ShaderDataType::Int3:			return GL_INT;
			case LWEngine::ShaderDataType::Int4:			return GL_INT;
			case LWEngine::ShaderDataType::Bool:			return GL_BOOL;
		}

		LWE_CORE_ASSERT(false, "ERROR_SHADER_DATA_TYPE::UNKNOWN_SHADER_DATA_TYPE");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		LWE_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		LWE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	void OpenGLVertexArray::Bind() const
	{
		LWE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		LWE_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		LWE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		LWE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "ERROR::VERTEX_BUFFER::VB_HAS_NO_LAYOUT");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), (const void*)element.Offset);
			
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		LWE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
	
		m_IndexBuffers = indexBuffer;
	}
	
}