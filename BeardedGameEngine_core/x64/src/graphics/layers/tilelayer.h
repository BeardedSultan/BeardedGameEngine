#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace beardedGameEngine { namespace graphics {

	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

} }
