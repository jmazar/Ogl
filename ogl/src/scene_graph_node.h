#ifndef _SCENE_GRAPH_NODE_H
#define _SCENE_GRAPH_NODE_H

#include <vector>
#include <memory>


class ISGNode {
public:


private:
	std::vector<std::unique_ptr<ISGNode>> m_children;

};

#endif