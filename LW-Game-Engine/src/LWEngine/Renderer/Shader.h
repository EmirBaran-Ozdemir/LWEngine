#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>


namespace LWEngine {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat(const std::string& name, GLfloat uniform);
		void UploadUniformVec2(const std::string& name, const glm::vec2& vector);
	private:
		uint32_t m_RendererID;
	};
}