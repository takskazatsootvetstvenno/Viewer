#pragma once
#include <string>
#include <memory>
#include <vector>

#include <unordered_map>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "mesh.h"
namespace TestEngine {

	class Model
	{
	public:
		Model(const std::string& path,
			std::unordered_map<std::string, Texture>& Textures,
			std::string default_shader_name);
		~Model() {};
		const std::vector<Mesh>& getMeshData() const;
		std::vector<Mesh>& getMeshData();
	private:
		std::string m_directory;
		std::string m_name;
		BufferLayout m_model_buffer_layout{
			ShaderDataType::Float3,
			ShaderDataType::Float3,
			ShaderDataType::Float2
		};
		std::vector<Mesh> m_vData;
	};
}
