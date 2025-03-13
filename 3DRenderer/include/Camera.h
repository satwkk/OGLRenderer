#pragma once

#include <glm/glm.hpp>

class CPerspectiveCamera
{
public:
	CPerspectiveCamera() = default;
	CPerspectiveCamera(const glm::vec3& initialPosition, float nearClipPlane, float farClipPlane, float winWidth, float winHeight, float fov);
	~CPerspectiveCamera();

	void Move(const glm::vec3& direction);
	void Rotate(float pitchOffset, float yawOffset);

	inline void SetPosition(const glm::vec3& position) { m_VPosition = position; SetupVPMatrix(); }
	inline void SetSpeed(float newSpeed) { m_fMoveSpeed = newSpeed; }

	inline const float GetSpeed() const { return m_fMoveSpeed; }
	inline const glm::vec3& GetPosition() const { return m_VPosition; }
	inline const glm::mat4& GetViewMatrix() const { return m_MViewMatrix; }
	inline glm::mat3 GetViewMatrixWithoutTranslation() { return glm::mat3(m_MViewMatrix); }
	inline const glm::mat4& GetProjectionMatrix() const { return m_MProjectionMatrix; }
	inline const glm::mat4& GetVPMatrix() const { return m_MViewProjectionMatrix; }

private:
	void SetupVPMatrix();

private:
	glm::mat4 m_MProjectionMatrix;
	glm::mat4 m_MViewMatrix;
	glm::mat4 m_MViewProjectionMatrix;
	glm::vec3 m_VPosition;
	glm::vec3 m_VRotationAxis;
	float m_fYaw;
	float m_fPitch;
	float m_fMoveSpeed;
	float m_fSensitivity;
};