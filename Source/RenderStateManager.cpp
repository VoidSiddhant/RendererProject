#include "RenderStateManager.h"
#include "Logger.h"

namespace EngineSpace
{
	PShader RenderStateManager::mp_shader = nullptr;
	LPD3D11EFFECT RenderStateManager::m_effect = nullptr;
	ID3DX11EffectTechnique* RenderStateManager::m_tech = nullptr;
	std::map<InputLayoutType, ID3D11InputLayout*> RenderStateManager::m_inputLayout_table = {};
	std::map<std::string, ID3DX11EffectMatrixVariable*> RenderStateManager::m_effectMatrix_table = {};
	std::vector<GameObject*> RenderStateManager::m_render_list = {};

	RenderStateManager::RenderStateManager()
	{

	}

	RenderStateManager::~RenderStateManager()
	{
		SG_UTIL_MEM_ReleaseCOM(m_effect);
		SG_UTIL_MEM_ReleaseCOM(m_tech);

		m_inputLayout_table.clear();
		m_effectMatrix_table.clear();
	}

	void RenderStateManager::ReleaseMem()
	{

	}
	// LOG : Building InputLayouts........................
	void RenderStateManager::BuildInputLayouts(const InputLayoutType type,...)
	{
		va_list typeList;
		va_start(typeList, type);
		InputLayoutType caseType = type;

		Logger buildLog("Builder");
		while (caseType != NULL)
		{
			buildLog.SetLog("Building InputLayout of type : %d",caseType);
			switch (caseType)
			{
				case InputLayoutType::POS_COLOR:
				{
					//Set Input Element structure Description (vertex structure used for rendering)
					D3D11_INPUT_ELEMENT_DESC inputDesc[] =
					{
						{ "POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
					{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
					};
					//Get Pass Description for InputSignature
					D3DX11_PASS_DESC passDesc;
					m_tech->GetPassByIndex(0)->GetDesc(&passDesc);
					ID3D11InputLayout* input;
					gp_RendererH->GetDevice()->CreateInputLayout(inputDesc, 2, passDesc.pIAInputSignature
						, passDesc.IAInputSignatureSize, &input);
					m_inputLayout_table.insert(std::pair<InputLayoutType, ID3D11InputLayout*>
						(caseType, input));
				}
				break;
				case InputLayoutType::POS_COLOR_TEXTURE :
				{

				}
				break;
			}
			
			buildLog.SetLog("Successfully Built InputLayout of type : %d",caseType);
			caseType = va_arg(typeList, InputLayoutType);
		}

		va_end(typeList);
	}

	void RenderStateManager::SetInputLayout(const InputLayoutType& type)
	{
		gp_RendererH->GetDeviceContext()->IASetInputLayout(const_cast<ID3D11InputLayout*>(m_inputLayout_table[type]));
	}

	void RenderStateManager::BuildShader(Shader* shader)
	{
		Logger builderLog("Builder");
		builderLog.SetLog("Building Shader");
		if (mp_shader != nullptr)
		{
			//TODO::Cache recent shaders here
			SG_UTIL_MEM_FREE(mp_shader);
		}
		mp_shader = shader;
		builderLog.SetLog("Shader Built");
		BuildShaderFX();
	}

	void RenderStateManager::BuildShaderFX()
	{
		UINT shaderFlags = 0;
#if defined(DEBUG) ||defined(_DEBUG)
		shaderFlags = D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
		Logger builderLog("Builder");
		builderLog.SetLog("Building FX from shader object %s", mp_shader->location);
		HRESULT hr = D3DX11CreateEffectFromFile(&mp_shader->location[0]
			, shaderFlags, gp_RendererH->GetDevice(), &m_effect);

		m_tech = m_effect->GetTechniqueByName(&mp_shader->tech_name[0]);
	
		for (int i = 0; i < mp_shader->cb_count; i++)
		{
			//Get Constant Buffer variable name
			std::string effect_variable_name = mp_shader->cbuffers[i];
			//Check map for present value

			ID3DX11EffectMatrixVariable* effect = m_effect->GetVariableByName(&effect_variable_name[0])->AsMatrix();
			//TODO::use map here
			m_effectMatrix_table.insert(std::pair<std::string, ID3DX11EffectMatrixVariable*>(effect_variable_name, effect));
		}
		builderLog.SetLog("Building FX from shader object %s complete", mp_shader->location);
	}

	void RenderStateManager::AddToRenderObjectList(GameObject* object)
	{
		m_render_list.push_back(object);
	}

};