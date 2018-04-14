#include "Shader.h"

namespace EngineSpace
{
	Shader::Shader()
	{
		location = L"NULL";
		cb_count = 0;
		tech_name = "NULL";
	}

	Shader::Shader(const Shader& copy_object)
	{
		*this = copy_object;
	}

	Shader::Shader(std::wstring location_cso, std::string TechniqueName
		, int COUNT_constant_buffers, std::vector<std::string> cbuffer_list)
	{
		location = location_cso;
		cb_count = COUNT_constant_buffers;
		tech_name = TechniqueName;
		cbuffers = cbuffer_list;
	}
	
}