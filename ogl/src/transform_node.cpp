#include "transform_node.h"
#include "matrix_stack.h"

void TransformNode::Render(float in_delta, Camera const & in_camera) {
	MatrixStack::Instance()->Push(m_transform);

	//Render children
	
	MatrixStack::Instance()->Pop();
}

void TransformNode::SetTransform(glm::mat4 const & in_transform) {
	m_transform = in_transform;
}
