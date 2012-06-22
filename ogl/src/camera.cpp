#include "camera.h"

Camera::Camera() {
	m_CameraTranslation = glm::mat4(1.0);
	m_CameraRotation = glm::mat4(1.0);
}

glm::mat4 const Camera::GetViewMatrix() const {
	return glm::inverse(m_CameraRotation * m_CameraTranslation);
}

glm::mat4 const Camera::GetWorldMatrix() const {
	return m_CameraRotation * m_CameraTranslation;
}

void Camera::SetCameraTranslation(glm::vec3 const & in_translate) {
	m_CameraTranslation = glm::translate(glm::mat4(1.0), in_translate);
}

void Camera::SetCameraRotation(float in_angle, glm::vec3 const & in_axis) {
	m_CameraRotation = glm::rotate(glm::mat4(1.0), in_angle, in_axis);
}

glm::vec4 const Camera::GetEyePosVec() const {
	glm::vec4 row = glm::column(m_CameraRotation * m_CameraTranslation,3);
	return row;
}

