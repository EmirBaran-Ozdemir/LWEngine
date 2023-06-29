#pragma once

#include "LWEngine/Renderer/Shader.h"
#include <glm/glm.hpp>
typedef unsigned int GLenum;

namespace LWEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual const std::string& GetName() const override { return m_Name; }


		virtual void Bind() const override;
		virtual void Unbind() const override;

		// TODO clean that mess
		virtual void SetInt(const std::string& name, int values) override;
		virtual void SetFloat(const std::string& name, float values) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void SetVec2(const std::string& name, const glm::vec2& values) override;
		virtual void SetVec3(const std::string& name, const glm::vec3& values) override;
		virtual void SetVec4(const std::string& name, const glm::vec4& values) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& values) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& values) override;


		void UploadUniformInt(const std::string& name, int values);
		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformVec2(const std::string& name, const glm::vec2& values);
		void UploadUniformVec3(const std::string& name, const glm::vec3& values);
		void UploadUniformVec4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& values);
		void UploadUniformMat4(const std::string& name, const glm::mat4& values);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}