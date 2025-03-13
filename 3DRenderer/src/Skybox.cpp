#include "Skybox.h"
#include <GL/glew.h>

CSkybox::CSkybox() :
	m_CVertexArray({})
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
	gSBufferData.vBufferLayouts.push_back(SVertexAttributeLayout{ EVertexAttributeType::Float3, 0 });

	m_CVertexArray.SetVertexBuffer(gSBufferData);
	m_CCubeMap.InitCubeMap(paths);
	m_CVertexArray.PrepareVertexArray();
}

CSkybox::~CSkybox()
{
	m_CCubeMap.Release();
}

void CSkybox::OnRender(CShader& shader, CPerspectiveCamera& camera)
{
	// Set depth properties
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	// Set shader params for view projection
	shader.Bind();
	shader.SetUniformMatrix4("uProjection", camera.GetProjectionMatrix());
	shader.SetUniformMatrix4("uView", glm::mat4{ camera.GetViewMatrixWithoutTranslation() });

	// Bind VAO and cubemap texture
	m_CVertexArray.Bind();
	m_CCubeMap.Bind();

	// Draw the skybox
	glDrawArrays(GL_TRIANGLES, 0, gvVertices.size());

	// Unbind resources
	m_CCubeMap.UnBind();
	m_CVertexArray.UnBind();
	shader.UnBind();

	// Reset depth properties
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}