#include "ShaderResource.h"
namespace TestEngine {
	ShaderResource::ShaderResource()
	{
	}
	ShaderResource::~ShaderResource()
	{
	}
	void ShaderResource::load_resource()
	{
		m_shader_program = std::make_unique<ShaderProgram>(m_resource_path, fragment_path);
	}
	const ShaderProgram& ShaderResource::get_resource()
	{
		return *m_shader_program;
	}
	void ShaderResource::set_resource_path(const std::string& path)
	{
		m_resource_path = path;
		fragment_path = path.substr(0, path.find_last_of('.')) + ".frag";
	}

}