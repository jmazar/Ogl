#ifndef _MATRIX_STACK
#define _MATRIX_STACK

#include <memory>
#include <vector>
#include "glm\gtc\matrix_transform.hpp"


class MatrixStack {
public:
	static std::shared_ptr<MatrixStack> Instance();
	void Push(glm::mat4 const & in_matrix);
	std::vector<glm::mat4> const GetStack() const ;
private:
	MatrixStack() {};
	MatrixStack(MatrixStack const &) {};
	MatrixStack & operator=(MatrixStack const &) {};
	static std::shared_ptr<MatrixStack> m_pInstance;

	std::vector<glm::mat4> m_stack;

};

#endif