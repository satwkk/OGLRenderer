#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Scene.h"

class CModel;
class CMesh;

class CSceneRenderer
{
public:
	static void Draw(CScene& scene, CShader& shader);
	static void Draw(const std::shared_ptr<CModel>& pModel, const glm::vec3& position, CShader& shader);
	static void Draw(const std::shared_ptr<CMesh>& pMesh, glm::mat4& modelMatrix, const glm::vec3& position, CShader& shader);
};