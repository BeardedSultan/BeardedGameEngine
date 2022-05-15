#pragma once

#include <string>
#include <GL\glew.h>
#include <FreeImage.h>

namespace beardedGameEngine { namespace graphics {

	class Texture
	{
	private:
		std::string m_Path;
		GLuint m_TID; //texture ID
		unsigned int m_Width, m_Height;
	public:
		Texture(const std::string& path);
		~Texture();
		void bind() const;
		void unbind() const;

		inline const unsigned int getWidth() const { return m_Width; }
		inline const unsigned int getHeight() const { return m_Height; }
	private:
		GLuint load();

	};

} }