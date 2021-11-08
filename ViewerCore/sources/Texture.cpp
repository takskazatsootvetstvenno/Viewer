#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "LogManager.h"
namespace TestEngine {
	Texture::Texture(const std::string& filename)
	{
        stbi_set_flip_vertically_on_load(true);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
		unsigned char* data = stbi_load(filename.c_str(), &m_width, &m_height, &m_nrComponents, 0);
        if (data) {
            GLenum format = GL_RGB;
            switch (m_nrComponents)
            {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            }

            //  glBindTexture(GL_TEXTURE_2D, textureID);
            glTextureStorage2D(m_id, 1, GL_RGB8, m_width, m_height);
            glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);

            //   glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            stbi_image_free(data);
        }
        else {
            LogManager::Error() << "Failed to load texture: " << filename << LogManager::Show();
            stbi_image_free(data);
        }
	}
    Texture::Texture(Texture&& otherTexture) noexcept
        :m_width(otherTexture.m_width),
        m_height(otherTexture.m_height),
        m_nrComponents(otherTexture.m_nrComponents),
        m_id(otherTexture.m_id)
    {
        otherTexture.m_id = 0;
        m_width = 0;
        m_height = 0;
        m_nrComponents = 0;
    }
    Texture& Texture::operator=(Texture&& otherTexture) noexcept
    {
        m_width = otherTexture.m_width;
        m_height = otherTexture.m_height;
        m_nrComponents = otherTexture.m_nrComponents;
        m_id = otherTexture.m_id;

        otherTexture.m_id = 0;
        m_width = 0;
        m_height = 0;
        m_nrComponents = 0;
        return *this;
    }

    const unsigned int Texture::get_id() const
    {
        return m_id;
    }
    const void Texture::bind_texture_unit(unsigned int unit) const
    {
        glBindTextureUnit(0, m_id);
    }
}