#pragma once

#include "../utils/fileutils.h"
#include <GL\glew.h>

namespace beardedGameEngine { namespace graphics {

	class Shader
	{
	private:
		GLuint shader;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;
	};

} }