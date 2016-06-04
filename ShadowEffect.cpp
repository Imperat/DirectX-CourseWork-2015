#include "ShadowEffect.h"

void ShadowEffect::GetHandles()
{
	DepthMapHandle = Effect->GetTechniqueByName("depthMap");
	CubicShadowMappingHandle = Effect->GetTechniqueByName("cubicShadowMapping");
	AmbientHandle = Effect->GetTechniqueByName("ambient");
	WorldMatrixHandle = Effect->GetParameterByName(NULL, "worldMat");
	WorldViewProjMatHandle = Effect->GetParameterByName(NULL, "worldViewProjMat");
	CubeShadowMapHandle = Effect->GetParameterByName(NULL, "cubeShadowMap");
	CubeShadowMap2Handle = Effect->GetParameterByName(NULL, "cubeShadowMap2");
	CubeShadowMap3Handle = Effect->GetParameterByName(NULL, "cubeShadowMap3");
	EyePositionHandle = Effect->GetParameterByName(NULL, "eyePosition");
	LightPositionHandle = Effect->GetParameterByName(NULL, "lightPosition");
	LightNumberHandle = Effect->GetParameterByName(NULL, "lightNumber");
	ShadowPositionHandle = Effect->GetParameterByName(NULL, "shadowLightPosition");
	materialAmbientHandle = Effect->GetParameterByName(NULL, "materialAmbient");
	lightEnabled1Handle = Effect->GetParameterByName(NULL, "lightEnabled1");
	lightEnabled2Handle = Effect->GetParameterByName(NULL, "lightEnabled2");
	lightEnabled3Handle = Effect->GetParameterByName(NULL, "lightEnabled3");
}

bool ShadowEffect::ValidateTechniques()
{
	if(FAILED(Effect->ValidateTechnique(DepthMapHandle)))
	{
		MessageBoxA(NULL, "depth map technique validation failed.", NULL, MB_OK);
		return false;
	}
	if(FAILED(Effect->ValidateTechnique(CubicShadowMappingHandle)))
	{
		MessageBoxA(NULL, "cubic shadow mapping technique validation failed.", NULL, MB_OK);
		return false;
	}
	if(FAILED(Effect->ValidateTechnique(AmbientHandle)))
	{
		MessageBoxA(NULL, "ambient technique validation failed.", NULL, MB_OK);
		return false;
	}

	return true;
}

bool ShadowEffect::SetUp()
{
	if(!(Initialise()) )
	{
		return false;
	}

	GetHandles();

	if( !(ValidateTechniques()) )
	{
		return false;
	}

	return true;
}
void ShadowEffect::CleanUp()
{
	if (Effect != NULL)
	{
		Effect->Release();
		Effect = NULL;
	}
	if (_pErrorBuffer != NULL)
	{
		_pErrorBuffer->Release();
		_pErrorBuffer = NULL;
	}
}

bool ShadowEffect::Initialise()
{
	if (FAILED(D3DXCreateEffectFromFile(_pd3dDevice, _effectFileName.c_str(), NULL, NULL, D3DXSHADER_DEBUG, NULL, &Effect, &_pErrorBuffer)))
	{
		if (_pErrorBuffer)
		{
			MessageBoxA(NULL, (LPCSTR)(_pErrorBuffer->GetBufferPointer()), NULL, MB_OK);
		}
		return false;
	}
	return true;
}