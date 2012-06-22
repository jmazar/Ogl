#ifndef _RENDERER_H
#define _RENDERER_H

class SceneGraph;

class Renderer {
public:
	void Init();

private:
	SceneGraph m_SceneGraph;

};


#endif