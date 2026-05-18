#pragma once
#include <string>
#include <stdexcept>

namespace itd
{
	class Error : public std::runtime_error
	{
	public:
		Error(std::string _source, std::string _what)
			: runtime_error(std::move(_what)), m_source(std::move(_source)) {
		}

	public:
		const char* source() const { return m_source.c_str(); }

	private:
		std::string m_source;
	};
}