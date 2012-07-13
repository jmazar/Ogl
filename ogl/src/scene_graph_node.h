#ifndef _SCENE_GRAPH_NODE_H
#define _SCENE_GRAPH_NODE_H

#include <vector>
#include <memory>

class SceneGraph;

class ISGNode {
public:
	virtual void Draw(SceneGraph const & in_sceneGraph) = 0;

	void AddChild(std::vector<std::shared_ptr<ISGNode>> const & in_child) {
		m_children.push_back(in_child);
	}

protected:
	std::vector<std::shared_ptr<ISGNode>> m_children;

};

#endif