#ifndef _SHADER_H
#define _SHADER_H

#include "Util.h"

#define SHADER_COLOR L"x64/Debug/Color.cso"

namespace EngineSpace
{
	struct Shader
	{
		Shader();
		Shader(const Shader& copy_object);
		Shader(std::wstring location_cso, std::string TechniqueName, int COUNT_constant_buffers, std::vector<std::string> constant_buffers);
		
		std::wstring location;
		std::string  tech_name;
		int cb_count;
		std::vector<std::string> cbuffers;
	};

	typedef Shader* PShader;
};
#endif // !_SHADER_H

