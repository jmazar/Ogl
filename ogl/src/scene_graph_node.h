#ifndef _SCENE_GRAPH_NODE_H
#define _SCENE_GRAPH_NODE_H

#include <vector>
#include <memory>


class ISGNode {
public:
	virtual void Draw(float in_delta) = 0;


private:
	std::vector<std::unique_ptr<ISGNode>> m_children;

};

#endif