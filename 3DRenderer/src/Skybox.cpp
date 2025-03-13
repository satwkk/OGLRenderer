#include "Skybox.h"
#include <GL/glew.h>

Skybox::Skybox() :
	m_VAO({})
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
	m_VAO.SetVertexBuffer(vertices);
	m_CubeMap.InitCubeMap(paths);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}

Skybox::~Skybox()
{
	m_CubeMap.Release();
}

void Skybox::OnRender(Shader& shader, Camera& camera)
{
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	shader.Bind();
	shader.SetUniformMatrix4("uProjection", camera.GetProjectionMatrix());
	shader.SetUniformMatrix4("uView", glm::mat4{ camera.GetViewMatrixWithoutTranslation() });
	m_VAO.Bind();
	m_CubeMap.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_CubeMap.UnBind();
	m_VAO.UnBind();
	shader.UnBind();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}