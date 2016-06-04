#pragma once
#include "Shader.h"

class ShadowEffect
{
	void GetHandles();
	bool ValidateTechniques();

protected:
	ID3DXBuffer* _pErrorBuffer;
	IDirect3DDevice9* _pd3dDevice;
	std::string _effectFileName;

public:
	ID3DXEffect* Effect;
	D3DXHANDLE DepthMapHandle;
	D3DXHANDLE CubicShadowMappingHandle;
	D3DXHANDLE AmbientHandle;
	D3DXHANDLE WorldMatrixHandle;
	D3DXHANDLE WorldViewProjMatHandle;
	D3DXHANDLE CubeShadowMapHandle;
	D3DXHANDLE CubeShadowMap2Handle;
	D3DXHANDLE CubeShadowMap3Handle;
	D3DXHANDLE EyePositionHandle;
	D3DXHANDLE LightPositionHandle;
	D3DXHANDLE LightNumberHandle;
	D3DXHANDLE ShadowPositionHandle;
	D3DXHANDLE materialAmbientHandle;
	D3DXHANDLE lightEnabled1Handle;
	D3DXHANDLE lightEnabled2Handle;
	D3DXHANDLE lightEnabled3Handle;


	ShadowEffect (IDirect3DDevice9** device, std::string effectFileName)
	{
		_pd3dDevice = *device;
		_effectFileName = effectFileName;
		Effect = NULL;
		_pErrorBuffer = NULL;
	}

	~ShadowEffect()
	{
		CleanUp();
	}

	bool SetUp();
	bool Initialise();
	void CleanUp();
};
