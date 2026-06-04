#pragma once
#include "in_the_dark/graphics/shader/shader_manager_api.h"
#include "in_the_dark/utility/resource_container.h"

namespace itd::graphics
{
	class ShaderManager : public ShaderManagerAPI
	{
	private:
		using Container = utility::ResourceContainer<std::string, ShaderAPI>;

	public:
		ShaderManager();
		~ShaderManager();

		ShaderManager(const ShaderManager&) = delete;
		ShaderManager(ShaderManager&&) = delete;

		ShaderManager& operator=(const ShaderManager&) = delete;
		ShaderManager& operator=(ShaderManager&&) = delete;

	public:
		static std::unique_ptr<ShaderManager> make_unique();

	public:
		void add(std::string _name, std::shared_ptr<ShaderAPI> _shader) override;
		std::shared_ptr<ShaderAPI> get(std::string _name) override;

	private:
		Container m_container;
	};
}