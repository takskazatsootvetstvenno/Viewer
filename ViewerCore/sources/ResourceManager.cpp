
#include "ResourceManager.h"
#include "Model.h"
#include <memory>

namespace TestEngine {
	const UniformBuffer& ResourceManager::getUBO(ResourceManager::GLOBAL_UBO UBOIndex) const
	{
		return m_vUBO[static_cast<unsigned int>(UBOIndex)];
	}
	void ResourceManager::addShaderProgram(const std::string& resourceName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		m_mShaders.try_emplace(resourceName, vertexShaderPath, fragmentShaderPath);
	}
	void ResourceManager::addModel(const std::string& modelPath)
	{
		Model newModel(modelPath, m_mTextures,"General");
		m_vMeshes.insert(m_vMeshes.end(),
			std::make_move_iterator(newModel.getMeshData().begin()),
			std::make_move_iterator(newModel.getMeshData().end()));
	}
	void ResourceManager::addTexture(const std::string& resourceName, const std::string& TexturePath)
	{
		m_mTextures.try_emplace(resourceName, TexturePath);
	}
	const ShaderProgram& ResourceManager::getShaderProgram(const std::string& resourceName)
	{
		return m_mShaders.find(resourceName)->second;
	}
	std::vector<Mesh>& ResourceManager::getMeshes()
	{
		return m_vMeshes;
	}
	const Texture& ResourceManager::getTexture(const std::string& resourceName)
	{
		return m_mTextures.find(resourceName)->second;
	}
	ResourceManager::ResourceManager()
	{
		init_values();
	}
	void ResourceManager::init_values()
	{
		addShaderProgram("General", "Shaders/General.vert", "Shaders/General.frag");
		addShaderProgram("Red", "Shaders/Red.vert", "Shaders/Red.frag");
		addModel("Models/map.objFile");

		BufferLayout buffer_layout_1mat4
		{
			ShaderDataType::Mat4,
			ShaderDataType::Mat4,
			ShaderDataType::Mat4
		};

		BindingUBO uboBinding;
		uboBinding.programID = getShaderProgram("General").getProgramID();
		uboBinding.uniformBlockIndex = getShaderProgram("General").getUniformBlockIndex("GlobalMatrices");
		m_vUBO.emplace_back(nullptr, buffer_layout_1mat4, uboBinding);
	}
}