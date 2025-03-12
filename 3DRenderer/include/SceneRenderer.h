#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Scene.h"

class Model;
class Mesh;

class SceneRenderer
{
public:
	static void Draw(Scene& scene, Shader& shader);
	static void Draw(const std::shared_ptr<Model>& model, const glm::vec3& position, Shader& shader);
	static void Draw(const std::shared_ptr<Mesh>& mesh, glm::mat4& modelMatrix, const glm::vec3& position, Shader& shader);
};