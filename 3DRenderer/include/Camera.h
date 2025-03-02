#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(const glm::vec3& initialPosition, float nearClipPlane, float farClipPlane, float winWidth, float winHeight, float fov);
	~Camera();

	void Move(const glm::vec3& direction);
	void Rotate(float pitchOffset, float yawOffset);

	inline void SetPosition(const glm::vec3& position) { m_Position = position; SetupVPMatrix(); }
	inline void SetSpeed(float newSpeed) { m_MoveSpeed = newSpeed; }

	inline const glm::vec3& GetPosition() const { return m_Position; }
	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	inline const glm::mat4& GetVPMatrix() const { return m_ViewProjectionMatrix; }

private:
	void SetupVPMatrix();

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;
	glm::vec3 m_Position;
	glm::vec3 m_RotationAxis;
	float m_Yaw;
	float m_Pitch;
	float m_MoveSpeed;
	float m_Sensitivity;
};