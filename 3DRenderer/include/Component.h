#pragma once

#include <memory>
#include <glm/glm.hpp>

class CMaterial;
class CMesh;
class CModel;

struct STransformComponent
{
	glm::vec3 VPosition{ glm::vec3(1.0) };
	glm::vec3 VScale{ glm::vec3(1.0f) };
	glm::vec3 VRotation{ glm::vec3(0.0f) };

	STransformComponent() = default;

	STransformComponent(const glm::vec3& pos) :
		VPosition(pos) {}

	STransformComponent(const glm::vec3& pos, const glm::vec3& rotation, const glm::vec3& scale) :
		VPosition(pos), VRotation(rotation), VScale(scale) {}

	STransformComponent(const glm::vec3& pos, const glm::vec3& scale) :
		VPosition(pos), VScale(scale) {}
};

struct SMeshRendererComponent
{
	std::shared_ptr<CModel> m_spCModelRef = nullptr;

	SMeshRendererComponent() = default;
	SMeshRendererComponent(const std::shared_ptr<CModel>& pModel) :
		m_spCModelRef(pModel)
	{
	}
};
