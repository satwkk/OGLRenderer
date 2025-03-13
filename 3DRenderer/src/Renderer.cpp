#include "Renderer.h"
#include "Logger.h"
#include "Shader.h"
#include "VertexArray.h"

CRenderer* CRenderer::s_pCInstance = nullptr;

bool CRenderer::Init()
{
	if (s_pCInstance == nullptr)
	{
		s_pCInstance = new CRenderer();
		return true;
	}

	verr << "Trying to instantiate another renderer. Aborting...\n";
	return false;
}

void CRenderer::ShutDown()
{
	delete s_pCInstance;
}

void CRenderer::Render(CShader& shader, SMeshRendererComponent& meshRenderer, STransformComponent& transformComponent)
{
	verr << "Not Implemented\n";
}
