#pragma once

#include "../renderable2d.h"
#include "../renderer2d.h"

namespace beardedGameEngine { namespace graphics {

	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		maths::mat4 m_ProjectionMatrix;
	public:
		Layer();
		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void render();

	};

} }
