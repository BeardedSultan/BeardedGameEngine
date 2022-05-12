#include "layer.h"


namespace beardedGameEngine { namespace graphics {
	Layer::Layer()
	{

	}
	Layer::~Layer()
	{
		delete m_Shader;
		delete m_Renderer;
		for (int i = 0; i < m_Renderables.size(); i++) {
			delete m_Renderables[i];
		}
	}
	void Layer::add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}
	void Layer::render()
	{
		m_Shader->enable();
		m_Shader->setUniformMat4
		m_Shader->disable();
	}

} }