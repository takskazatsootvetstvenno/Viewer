#pragma once
#include <string>
namespace TestEngine {
	class Texture {
	public:
		Texture(const std::string& filename);
		~Texture() {};
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&& otherTexture) noexcept;
		Texture& operator=(Texture&& otherTexture) noexcept;
		const unsigned int get_id() const;
		const void bind_texture_unit(unsigned int unit) const;
	private:
		Texture();
		int m_width;
		int m_height;
		int m_nrComponents;
		unsigned int m_id;
	};
}