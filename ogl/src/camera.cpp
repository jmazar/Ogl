#include "camera.h"

Camera::Camera() {
	m_cameraTranslation = glm::mat4(1.0);
	m_cameraRotation = glm::mat4(1.0);
	m_projectionMatrix = glm::perspective(60.0f, 640.f / 480.0f, 0.1f, 100.0f);
}

glm::mat4 const Camera::GetViewMatrix() const {
	return glm::inverse(m_cameraRotation * m_cameraTranslation);
}

glm::mat4 const Camera::GetWorldMatrix() const {
	return m_cameraRotation * m_cameraTranslation;
}

glm::mat4 const Camera::GetProjectionMatrix() const {
	return m_projectionMatrix;
}

void Camera::SetCameraTranslation(glm::vec3 const & in_translate) {
	m_cameraTranslation = glm::translate(glm::mat4(1.0), in_translate);
}

void Camera::SetCameraRotation(float in_angle, glm::vec3 const & in_axis) {
	m_cameraRotation = glm::rotate(glm::mat4(1.0), in_angle, in_axis);
}

glm::vec4 const Camera::GetEyePosVec() const {
	glm::vec4 row = glm::column(m_cameraRotation * m_cameraTranslation,3);
	return row;
}

