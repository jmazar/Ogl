#ifndef _CAMERA_H
#define _CAMREA_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"

class Camera {
public:
	Camera();
	glm::mat4 const GetViewMatrix() const;
	glm::mat4 const GetWorldMatrix() const;
	glm::mat4 const GetProjectionMatrix() const;
	void SetCameraTranslation(glm::vec3 const & in_translate);
	void SetCameraRotation(float in_angle, glm::vec3 const & in_axis);
	glm::vec4 const GetEyePosVec() const;
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_cameraRotation;
	glm::mat4 m_cameraTranslation;
};

#endif 