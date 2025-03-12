#pragma once

#include <vector>
#include <memory>
#include <entt.hpp>
#include <unordered_map>

#include "Logger.h"
#include "Shader.h"
#include "Utility.h"

class SceneObject;
class Model;
class Shader;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	void InitScene();
	void OnUpdate(Shader& shader);
	void CloseScene();

	inline entt::registry& GetSceneRegistry() { return m_Registry; }
	inline std::shared_ptr<Model>& GetEntityModel(const entt::entity entity) {
		auto it = m_SceneObjects.find(entity);
		ASSERT(it != m_SceneObjects.end());
		return it->second;
	}

private:
	// TODO: Replace with scene objects later
	std::unordered_map<entt::entity, std::shared_ptr<Model>> m_SceneObjects;
	entt::registry m_Registry;
};