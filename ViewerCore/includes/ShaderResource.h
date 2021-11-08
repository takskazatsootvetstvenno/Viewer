#pragma once
#include "IResource.h"
#include "ShaderProgram.h"
#include <unordered_map>
#include <memory>
namespace TestEngine {
	class ShaderResource : public IResource
	{
	public:
		ShaderResource();
		virtual ~ShaderResource() override;
		void load_resource() override;
		const ShaderProgram& get_resource();
		void set_resource_path(const std::string& path) override;
	private:
		std::unique_ptr<ShaderProgram> m_shader_program;
		std::string fragment_path;
	};
}
