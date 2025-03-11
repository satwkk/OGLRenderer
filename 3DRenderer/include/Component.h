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

	TransformComponent() = default;
	TransformComponent(const glm::vec3& pos) :
		Position(pos) {}
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
