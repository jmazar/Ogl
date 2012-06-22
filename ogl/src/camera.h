#ifndef _CAMERA
#define _CAMREA

#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
  Camera();
  glm::mat4 const GetViewMatrix() const;
  glm::mat4 const GetWorldMatrix() const;
  void SetCameraTranslation(glm::vec3 const & in_translate);
  void SetCameraRotation(float in_angle, glm::vec3 const & in_axis);
private:
  glm::mat4 m_CameraTranslation;
  glm::mat4 m_CameraRotation;
};

#endif 