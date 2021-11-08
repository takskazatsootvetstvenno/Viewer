#include "Mesh.h"

namespace TestEngine {

	Mesh::Mesh(MeshData mesh_info)
		:m_data(std::move(mesh_info))
	{
	}
	void Mesh::setShaderByName(std::string shader_name)
	{
		m_data.m_Shader_name = shader_name;
	}

	void Mesh::setTextureByName(std::string texture_name)
	{
		m_data.m_Texture_name = texture_name;
	}

	const MeshData& Mesh::get_mesh_data() const
	{
		return m_data;
	}
}