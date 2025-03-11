#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec3& initialPosition, float nearClipPlane, float farClipPlane, float winWidth, float winHeight, float fov) :
	m_ViewMatrix(glm::mat4(1.0f)),
	m_ProjectionMatrix(glm::perspective(fov, winWidth / winHeight, nearClipPlane, farClipPlane)),
	m_MoveSpeed(1.f),
	m_Position(initialPosition),
	m_Yaw(0.0f),
	m_Pitch(0.0f),
	m_Sensitivity(0.7f),
	m_RotationAxis(glm::vec3(0.0f, 1.0f, 0.0f))
{
	m_ViewMatrix = glm::lookAt(initialPosition, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	SetupVPMatrix();
}

Camera::~Camera()
{
}

void Camera::Move(const glm::vec3& direction)
{
	if (direction == glm::vec3(0.0f, 0.0f, 0.0f))
		return;
	auto rotationMatrix = glm::mat3(m_ViewMatrix);
	auto worldDirection = glm::transpose(rotationMatrix) * direction;
	m_Position += worldDirection * m_MoveSpeed;
	SetupVPMatrix();
}

void Camera::Rotate(float pitchOffset, float yawOffset)
{
	m_Yaw += yawOffset * m_Sensitivity;
	m_Pitch += pitchOffset * m_Sensitivity;
	m_Pitch = glm::clamp(m_Pitch, -90.f, 90.f);
	SetupVPMatrix();
}

void Camera::SetupVPMatrix()
{
	// Get the yaw and pitch matrix
	glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));

	// Combine both to get composite rotation
	glm::mat4 rotationMatrix = yawMatrix * pitchMatrix;

	// Translation for view matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -m_Position);

	// Combine all together to get final view projection matrix
	m_ViewMatrix = glm::transpose(rotationMatrix) * translationMatrix;
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
