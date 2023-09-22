#pragma once

#include "LWEngine/Scene/Scene.h"

namespace LWEngine {

	class SceneSerializer
	{
	public:
		SceneSerializer() = default;
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

		bool HasScene() const { return m_Scene != nullptr; }
	private:
		Ref<Scene> m_Scene;
	};
}