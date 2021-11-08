#pragma once
#include<string>
namespace TestEngine {
	class IResource
	{
	public:
		IResource() {};
		virtual ~IResource() {};
		virtual void set_resource_path(const std::string& path) = 0;
		virtual void load_resource() = 0;
		IResource(const IResource&) = delete;
		IResource& operator=(const IResource&) = delete;
		//IResource(IResource&& other) noexcept;
		//IResource& operator=(IResource&& other) noexcept;
		//std::string get_name() const;
	protected:
		std::string m_resource_path;
	};
}
