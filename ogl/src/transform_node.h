#ifndef _TRANSFORM_NODE_H
#define _TRANSFORM_NODE_H

#include "scene_graph_node.h"
#include "glm\gtc\matrix_transform.hpp"

class TransformNode : public ISGNode {
public:
	void Render(float in_delta, Camera const & in_camera);
	void SetTransform(glm::mat4 const & in_transform);
private:
	glm::mat4 m_transform;
};

#endif
