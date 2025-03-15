#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Component.h"
#include "Scene.h"

class CModel;
class CMesh;

class CSceneRenderer
{
public:
	static void Draw(CScene& scene, CShader& shader);
	static void Draw(const std::shared_ptr<CModel>& pCModel, STransformComponent& transform, CShader& shader);
	static void Draw(const std::shared_ptr<CMesh>& pCMesh, glm::mat4& modelMatrix, STransformComponent& transform, CShader& shader);
};
