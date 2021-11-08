#pragma once
#include <string>
#include "IndexBuffer.h"
#include "LogManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
namespace TestEngine {
	struct MeshData
	{
		std::string m_Texture_name;
		std::string m_Shader_name;
		VertexBuffer m_VBO;
		IndexBuffer m_EBO;
		VertexArray m_VAO;
	};
	class Mesh
	{
	public:
		Mesh(MeshData mesh_info);
		void setShaderByName(std::string shader_name);
		void setTextureByName(std::string texture_name);
		const MeshData& get_mesh_data() const;

	private:
		MeshData m_data;
	};
}
