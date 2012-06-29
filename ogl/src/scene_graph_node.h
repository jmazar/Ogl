#ifndef _SCENE_GRAPH_NODE_H
#define _SCENE_GRAPH_NODE_H

#include <vector>
#include <memory>

class Camera;

class ISGNode {
public:
	virtual void Draw(float in_delta, Camera const & in_camera) = 0;
	//TODO: Implement? Not sure how to deal with unique_ptr stuff...
	//void AddChild(std::vector<std::unique_ptr<ISGNode>> const & in_child);

private:
	std::vector<std::unique_ptr<ISGNode>> m_children;

};

#endif