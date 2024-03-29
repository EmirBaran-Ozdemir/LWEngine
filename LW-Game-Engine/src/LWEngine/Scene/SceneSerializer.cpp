#include "lwpch.h"
#include "SceneSerializer.h"

#include "LWEngine/Scene/Entity.h"
#include "Components.h"

#include <fstream>
#define YAML_CPP_STATIC_DEFINE
#include <yaml-cpp/yaml.h>

#define _KeyN << YAML::Key
#define _ValN << YAML::Value
#define _Key(x) << YAML::Key << x
#define _Val(x) << YAML::Value << x
#define _KeyVal(x, y) _Key(x) _Val(y)

#define _BeginMap << YAML::BeginMap
#define _EndMap << YAML::EndMap
#define _BeginSeq << YAML::BeginSeq
#define _EndSeq << YAML::EndSeq
#define _Flow << YAML::Flow

namespace LWEngine {

	namespace Utils {
		static std::string RigidBodyTypeToString(Rigidbody2DComponent::BodyType type)
		{
			switch (type)
			{
				case Rigidbody2DComponent::BodyType::Static:	return "Static";
				case Rigidbody2DComponent::BodyType::Dynamic:	return "Dynamic";
				case Rigidbody2DComponent::BodyType::Kinematic:	return "Kinematic";
			}
			LWE_CORE_ASSERT(false, "ERROR::CONVERSION::UNKNOWN_BODY_TYPE");
			return "UNKNOWN";
		}
		static Rigidbody2DComponent::BodyType StringToRigidBodyType(const std::string& typeString)
		{
			if (typeString == "Static")		return Rigidbody2DComponent::BodyType::Static;
			else if (typeString == "Dynamic")		return Rigidbody2DComponent::BodyType::Dynamic;
			else if (typeString == "Kinematic")		return Rigidbody2DComponent::BodyType::Kinematic;

			LWE_CORE_ASSERT(false, "ERROR::CONVERSION::UNKNOWN_BODY_TYPE");
			return Rigidbody2DComponent::BodyType::Static;
		}
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out _Flow;
		out _BeginSeq << v.x << v.y _EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out _Flow;
		out _BeginSeq << v.x << v.y << v.z _EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out _Flow;
		out _BeginSeq << v.x << v.y << v.z << v.w _EndSeq;
		return out;
	}


	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{

	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out _BeginMap;
		out _KeyVal("Entity", entity.GetUUID());
		if (entity.HasComponent<TagComponent>())
		{
			out _Key("TagComponent");
			out _BeginMap;
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out _KeyVal("Tag", tag);
			out _EndMap;
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out _Key("TransformComponent");
			out _BeginMap;
			auto& transformComp = entity.GetComponent<TransformComponent>();
			out _KeyVal("Translation", transformComp.Translation);
			out _KeyVal("Rotation", transformComp.Rotation);
			out _KeyVal("Scale", transformComp.Scale);
			out _EndMap;
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out _Key("CameraComponent");
			out _BeginMap;

			auto& cameraComp = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComp.Camera;

			out _Key("Camera");
			out _ValN;
			out _BeginMap;
			out _KeyVal("ProjectionType", (int)camera.GetProjectionType());
			out _KeyVal("PerspectiveFOV", camera.GetPerspectiveVerticalFOV());
			out _KeyVal("PerspectiveNear", camera.GetPerspectiveNearClip());
			out _KeyVal("PerspectiveFar", camera.GetPerspectiveFarClip());
			out _KeyVal("OrthographicSize", camera.GetOrthographicSize());
			out _KeyVal("OrthographicNear", camera.GetOrthographicNearClip());
			out _KeyVal("OrthographicFar", camera.GetOrthographicFarClip());
			out _EndMap;

			out _KeyVal("Primary", cameraComp.Primary);
			out _KeyVal("FixedAspectRatio", cameraComp.FixedAspectRatio);
			out _EndMap;
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out _Key("SpriteRendererComponent");
			out _BeginMap;
			auto& spriteRendererComp = entity.GetComponent<SpriteRendererComponent>();
			out _KeyVal("Color", spriteRendererComp.Color);
			if (spriteRendererComp.Texture)
			{
				out _KeyVal("TextureLocation", spriteRendererComp.Texture->GetPath());
			}
			out _EndMap;
		}

		if (entity.HasComponent<Rigidbody2DComponent>())
		{
			out _Key("Rigidbody2DComponent");
			out _BeginMap;
			auto& rb2DComp = entity.GetComponent<Rigidbody2DComponent>();
			out _KeyVal("BodyType", Utils::RigidBodyTypeToString(rb2DComp.Type));
			out _KeyVal("FixedRotation", rb2DComp.FixedRotation);
			out _EndMap;
		}

		if (entity.HasComponent<BoxCollider2DComponent>())
		{
			out _Key("BoxCollider2DComponent");
			out _BeginMap;
			auto& bc2DComp = entity.GetComponent<BoxCollider2DComponent>();
			out _KeyVal("Offset", bc2DComp.Offset);
			out _KeyVal("Size", bc2DComp.Size);
			out _KeyVal("Density", bc2DComp.Density);
			out _KeyVal("Friction", bc2DComp.Friction);
			out _KeyVal("Restitution", bc2DComp.Restitution);
			out _KeyVal("RestitutionThreshold", bc2DComp.RestitutionThreshold);
			out _EndMap;
		}
		out _EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out _BeginMap;

		out _KeyVal("Scene", "Name");
		out _Key("Entities") _BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity = { entityID,m_Scene.get() };
				if (!entity)
					return;
				SerializeEntity(out, entity);
			});

		out _EndSeq;
		out _EndMap;
		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		LWE_CORE_ASSERT(false, "NOT::IMPLEMENTED");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node data = YAML::LoadFile(filepath);

		if (!data["Scene"])
			return false;
		std::string sceneName = data["Scene"].as<std::string>();
		LWE_CORE_TRACE("Deserializing Scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>();

				std::string name;
				auto tagComp = entity["TagComponent"];
				if (tagComp)
					name = tagComp["Tag"].as<std::string>();
				LWE_CORE_TRACE("Deserializing entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntityWithUUID(uuid, name);

				auto transformComp = entity["TransformComponent"];
				if (transformComp)
				{
					auto& entityTC = deserializedEntity.GetComponent<TransformComponent>();
					entityTC.Translation = transformComp["Translation"].as<glm::vec3>();
					entityTC.Rotation = transformComp["Rotation"].as<glm::vec3>();
					entityTC.Scale = transformComp["Scale"].as<glm::vec3>();
				}

				auto cameraComp = entity["CameraComponent"];
				if (cameraComp)
				{
					auto& entityCC = deserializedEntity.AddComponent<CameraComponent>();
					auto& cameraProps = cameraComp["Camera"];
					entityCC.Camera.SetProjectionType(cameraProps["ProjectionType"].as<int>());

					entityCC.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
					entityCC.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
					entityCC.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

					entityCC.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					entityCC.Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
					entityCC.Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

					entityCC.Primary = cameraComp["Primary"].as<bool>();
					entityCC.FixedAspectRatio = cameraComp["FixedAspectRatio"].as<bool>();
				}

				auto spriteRendererComp = entity["SpriteRendererComponent"];
				if (spriteRendererComp)
				{
					auto& entitySRC = deserializedEntity.AddComponent<SpriteRendererComponent>();
					entitySRC.Color = spriteRendererComp["Color"].as<glm::vec4>();
					if (spriteRendererComp["TextureLocation"])
						entitySRC.Texture = Texture2D::Create(spriteRendererComp["TextureLocation"].as<std::string>());
				}

				auto rigidBodyComp = entity["Rigidbody2DComponent"];
				if (rigidBodyComp)
				{
					auto& entityRBC = deserializedEntity.AddComponent<Rigidbody2DComponent>();
					entityRBC.Type = Utils::StringToRigidBodyType(rigidBodyComp["BodyType"].as<std::string>());
					entityRBC.FixedRotation = rigidBodyComp["FixedRotation"].as<bool>();
				}

				auto boxCollider2DComponent = entity["BoxCollider2DComponent"];
				if (boxCollider2DComponent)
				{
					auto& entityBCC = deserializedEntity.AddComponent<BoxCollider2DComponent>();
					entityBCC.Offset = boxCollider2DComponent["Offset"].as<glm::vec2>();
					entityBCC.Size = boxCollider2DComponent["Size"].as<glm::vec2>();

					entityBCC.Density = boxCollider2DComponent["Density"].as<float>();
					entityBCC.Friction = boxCollider2DComponent["Friction"].as<float>();
					entityBCC.Restitution = boxCollider2DComponent["Restitution"].as<float>();
					entityBCC.RestitutionThreshold = boxCollider2DComponent["RestitutionThreshold"].as<float>();
				}
			}
		}
		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		LWE_CORE_ASSERT(false, "NOT::IMPLEMENTED");
		return false;
	}
}

namespace YAML {
	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}
		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}
		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}
