#pragma once

#include <vector>
#include <memory>
#include <entt.hpp>
#include <unordered_map>

class SceneObject;
class Model;
class Shader;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	void InitDebugScene();
	void OnUpdate(std::shared_ptr<Shader>& shader);

private:
	// TODO: Replace with game objects later
	std::vector<std::shared_ptr<Model>> m_DebugModels;
	std::unordered_map<entt::entity, std::shared_ptr<Model>> m_SceneObjects;
	entt::registry m_Registry;
};