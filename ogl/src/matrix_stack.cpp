#include "matrix_stack.h"

std::shared_ptr<MatrixStack> MatrixStack::m_pInstance;

std::shared_ptr<MatrixStack> MatrixStack::Instance() {
	if(NULL == m_pInstance.get())
		m_pInstance.reset(new MatrixStack());

	return m_pInstance;
}

void MatrixStack::Push(glm::mat4 const & in_matrix) {
	m_stack.push_back(in_matrix);
}

std::vector<glm::mat4> const MatrixStack::GetStack() const {
	return m_stack;
}
