#pragma once

#include <memory>
#include <glm/glm.hpp>

class Material;
class Mesh;
class VertexBuffer;
class IndexBuffer;
class Model;

struct TransformComponent
{
	glm::vec3 Position{ glm::vec3(1.0) };
	glm::vec3 Scale{ glm::vec3(1.0f) };

	TransformComponent() = default;
	TransformComponent(const glm::vec3& pos) :
		Position(pos) {}
	TransformComponent(const glm::vec3& pos, const glm::vec3& scale) :
		Position(pos), Scale(scale) {
	}
};

struct MeshRendererComponent
{
	std::shared_ptr<Model> ModelRef = nullptr;

	MeshRendererComponent() = default;
	MeshRendererComponent(const std::shared_ptr<Model>& model) :
		ModelRef(model)
	{
	}
};
