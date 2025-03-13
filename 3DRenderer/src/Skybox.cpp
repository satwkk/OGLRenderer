#include "Skybox.h"
#include <GL/glew.h>

CSkybox::CSkybox() :
	m_cVertexArray({})
{
	std::vector<std::string> paths
	{
		"./res/skybox/right.jpg",
		"./res/skybox/left.jpg",
		"./res/skybox/top.jpg",
		"./res/skybox/bottom.jpg",
		"./res/skybox/front.jpg",
		"./res/skybox/back.jpg",
	};

	gSBufferData.vVertices = gvVertices;
	gSBufferData.vBufferLayouts.push_back({ EVertexAttributeType::Float3, 0 });

	m_cVertexArray.SetVertexBuffer(gSBufferData);
	m_cCubeMap.InitCubeMap(paths);
	m_cVertexArray.PrepareVertexArray();
}

CSkybox::~CSkybox()
{
	m_cCubeMap.Release();
}

void CSkybox::OnRender(CShader& shader, CPerspectiveCamera& camera)
{
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	shader.Bind();
	shader.SetUniformMatrix4("uProjection", camera.GetProjectionMatrix());
	shader.SetUniformMatrix4("uView", glm::mat4{ camera.GetViewMatrixWithoutTranslation() });
	m_cVertexArray.Bind();
	m_cCubeMap.Bind();
	glDrawArrays(GL_TRIANGLES, 0, gvVertices.size());
	m_cCubeMap.UnBind();
	m_cVertexArray.UnBind();
	shader.UnBind();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}