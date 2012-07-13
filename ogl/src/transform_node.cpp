#include "transform_node.h"
#include "matrix_stack.h"

void TransformNode::Render(SceneGraph const & in_sceneGraph) {
	MatrixStack::Instance()->Push(m_transform);

	//Render children
	for(auto iterator = m_children.begin(); iterator != m_children.end(); iterator++) {
		(*iterator)->Draw(in_sceneGraph);
	}

	MatrixStack::Instance()->Pop();
}

void TransformNode::SetTransform(glm::mat4 const & in_transform) {
	m_transform = in_transform;
}
