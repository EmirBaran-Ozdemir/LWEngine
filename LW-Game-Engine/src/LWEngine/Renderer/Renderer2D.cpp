#include "lwpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace LWEngine {

	struct Renderer2DStorage
	{
		Ref<LWEngine::Shader> quadTextureShader;
		Ref<LWEngine::VertexArray> quadVA;
		Ref<LWEngine::Texture2D> whiteTexture;

	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		LWE_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();

		s_Data->quadVA = LWEngine::VertexArray::Create();
		float squareVertices[5 * 4] = {
			// Positions      // Texture Coordinates
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		LWEngine::Ref<LWEngine::VertexBuffer> squareVB;
		squareVB.reset(LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		LWEngine::BufferLayout squareLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVB->SetLayout(squareLayout);
		s_Data->quadVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		Ref<LWEngine::IndexBuffer> squareIB;
		squareIB.reset((LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		s_Data->quadVA->SetIndexBuffer(squareIB);

		s_Data->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data->quadTextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->quadTextureShader->Bind();
		s_Data->quadTextureShader->SetInt("u_Texture2D", 0);
	}

	void Renderer2D::Shutdown()
	{
		LWE_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		LWE_PROFILE_FUNCTION();

		s_Data->quadTextureShader->Bind();
		s_Data->quadTextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		LWE_PROFILE_FUNCTION();

		s_Data->quadTextureShader->Unbind();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		LWE_PROFILE_FUNCTION();

		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		LWE_PROFILE_FUNCTION();

		s_Data->quadTextureShader->SetFloat4("u_Color", color);
		// White shader 
		s_Data->whiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->quadTextureShader->SetMat4("u_Transform", transform);

		s_Data->quadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVA);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		LWE_PROFILE_FUNCTION();

		s_Data->quadTextureShader->SetFloat4("u_Color", glm::vec4(1.0f));

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y, 1.0f });
		s_Data->quadTextureShader->SetMat4("u_Transform", transform);

		s_Data->quadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVA);
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint)
	{
		LWE_PROFILE_FUNCTION();

		s_Data->quadTextureShader->SetFloat4("u_Color", tint);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y, 1.0f });
		s_Data->quadTextureShader->SetMat4("u_Transform", transform);

		s_Data->quadVA->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVA);
	}
}