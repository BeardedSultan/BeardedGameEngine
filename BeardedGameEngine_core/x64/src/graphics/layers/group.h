#pragma once

#include "../renderable2d.h"

namespace beardedGameEngine { namespace graphics {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		maths::mat4 m_TransformationMatrix;
	public:
		Group(const maths::mat4& transform);
		void submit(Renderer2D* renderer) const override;
		void add(Renderable2D* renderable);
	};

} }