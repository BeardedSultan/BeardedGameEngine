#include "texture.h"

namespace beardedGameEngine { namespace graphics {

	Texture::Texture(const std::string& filename)
		: m_FileName(filename)
	{
		m_TID = load();
	}

	Texture::~Texture()
	{

	}

	void Texture::bind() const 
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::unbind() const 
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::load()
	{
		BYTE* pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);

		GLuint result;

		//generate an OpenGL texture ID for this texture
		glGenTextures(1, &result);
		//bind to the new texture ID
		glBindTexture(GL_TEXTURE_2D, result);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//store the texture data for OpenGL use
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		//delete[] pixels

		return result;
	}

} }