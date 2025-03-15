#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CPerspectiveCamera::CPerspectiveCamera(const glm::vec3& initialPosition, float nearClipPlane, float farClipPlane, float winWidth, float winHeight, float fov) :
	m_MViewMatrix(glm::mat4(1.0f)),
	m_MProjectionMatrix(glm::perspective(glm::radians(fov), winWidth / winHeight, nearClipPlane, farClipPlane)),
	m_fMoveSpeed(1.f),
	m_VPosition(initialPosition),
	m_fYaw(0.0f),
	m_fPitch(0.0f),
	m_fSensitivity(0.7f),
	m_VRotationAxis(glm::vec3(0.0f, 1.0f, 0.0f))
{
	m_MViewMatrix = glm::lookAt(initialPosition, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	SetupVPMatrix();
}

CPerspectiveCamera::~CPerspectiveCamera()
{
}

void CPerspectiveCamera::OnUpdate(CShader& cameraShaderInstance)
{
	if (!cameraShaderInstance.IsBound()) 
		cameraShaderInstance.Bind();
	cameraShaderInstance.SetUniformMatrix4("uVPMatrix", m_MViewProjectionMatrix);
}

void CPerspectiveCamera::Move(const glm::vec3& direction)
{
	if (direction == glm::vec3(0.0f, 0.0f, 0.0f))
		return;
	auto MRotationMatrix = glm::mat3(m_MViewMatrix);
	auto MWorldDirection = glm::transpose(MRotationMatrix) * direction;
	m_VPosition += MWorldDirection * m_fMoveSpeed;
	SetupVPMatrix();
}

void CPerspectiveCamera::Rotate(float pitchOffset, float yawOffset)
{
	m_fYaw += yawOffset * m_fSensitivity;
	m_fPitch += pitchOffset * m_fSensitivity;
	m_fPitch = glm::clamp(m_fPitch, -90.f, 90.f);
	SetupVPMatrix();
}

void CPerspectiveCamera::SetupVPMatrix()
{
	// Get the yaw and pitch matrix
	glm::mat4 MYawMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_fYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 MPitchMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_fPitch), glm::vec3(1.0f, 0.0f, 0.0f));

	// Combine both to get composite rotation
	glm::mat4 MRotationMatrix = MPitchMatrix * MYawMatrix;

	// Translation for view matrix
	glm::mat4 MTranslationMatrix = glm::translate(glm::mat4(1.0f), -m_VPosition);

	// Combine all together to get final view projection matrix
	m_MViewMatrix = MRotationMatrix * MTranslationMatrix;
	m_MViewProjectionMatrix = m_MProjectionMatrix * m_MViewMatrix;
}
