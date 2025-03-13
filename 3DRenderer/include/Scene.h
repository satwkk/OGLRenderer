#pragma once

#include <vector>
#include <memory>
#include <entt.hpp>
#include <unordered_map>

#include "Logger.h"
#include "Shader.h"
#include "Utility.h"

class SceneObject;
class CModel;
class CShader;

class CScene
{
public:
	CScene() = default;
	~CScene() = default;

	void InitScene();
	void OnUpdate(CShader& shader);
	void CloseScene();

	inline entt::registry& GetSceneRegistry() { return m_CRegistry; }
	inline std::shared_ptr<CModel>& GetEntityModel(const entt::entity entity) {
		auto it = m_umSceneObjectMap.find(entity);
		ASSERT(it != m_umSceneObjectMap.end());
		return it->second;
	}

private:
	// TODO: Replace with scene objects later
	std::unordered_map<entt::entity, std::shared_ptr<CModel>> m_umSceneObjectMap;
	entt::registry m_CRegistry;
};