#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Scene.h"

class Model;
class Mesh;

class SceneRenderer
{
public:
	static void Draw(Scene& scene, const std::shared_ptr<Shader>& shader);
	static void Draw(const std::shared_ptr<Model>& model, const glm::vec3& position, const std::shared_ptr<Shader>& shader);
	static void Draw(const std::shared_ptr<Mesh>& mesh, glm::mat4& modelMatrix, const glm::vec3& position, const std::shared_ptr<Shader>& shader);
};