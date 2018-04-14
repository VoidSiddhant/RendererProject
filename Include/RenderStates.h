#ifndef _RENDER_STATES_H
#define _RENDER_STATES_H
#include"Util.h"
#include <map>
#include "Shader.h"
#include "GameObject.h"
namespace EngineSpace
{
	enum InputLayoutType
	{
		POS_COLOR,
		POS_COLOR_TEXTURE
	};

	class RenderStateManager
	{
	public:
		RenderStateManager();
		~RenderStateManager();

		static void ReleaseMem();

		//Shader related
		static void BuildShader(Shader* shader);
		//Create device related states
		static void CreateInputLayout(const InputLayoutType& type);
		static void SetInputLayout(const InputLayoutType& type);
		static void AddToRenderObjectList(GameObject* object);
		
		static LPD3D11EFFECTMATRIXVARIABLE GetEffectVariable(std::string variableName) {
			return m_effectMatrix_table[variableName];
		}

		static ID3DX11EffectTechnique* GetEffectTechnique() {
			return m_tech;
		}

		//TODO Change here
		static std::vector<GameObject*> m_render_list;

	private:
		
		static void BuildShaderFX();

		static PShader mp_shader;
		static LPD3D11EFFECT m_effect;
		static ID3DX11EffectTechnique* m_tech;
		//TODO : MEM LEAK..................NOT RELEASED ..........................
		static std::map<InputLayoutType,ID3D11InputLayout*> m_inputLayout_table;
		static std::map<std::string, ID3DX11EffectMatrixVariable*> m_effectMatrix_table;
	};

};

#endif // !_RENDER_STATES_H
