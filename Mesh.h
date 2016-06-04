#pragma once
#include "d3dx9.h"
#include <string>
#include "ShadowEffect.h"

class Mesh
{
	IDirect3DDevice9* _pd3dDevice;
	D3DXMATRIXA16 _worldMatrix;
	DWORD _numMaterials;
	std::string _meshFileName;
	ID3DXBuffer* _matBuffer;

public:
	ID3DXMesh* _pMesh;
	D3DXVECTOR4 Color;

	Mesh(IDirect3DDevice9* device, std::string meshFileName, D3DXVECTOR4 tColor);
	~Mesh();

	D3DXMATRIXA16* GetWorldMat();
	void Translate(float inX, float inY, float inZ);

	bool Load();
	void RenderAmbient(D3DXMATRIXA16* inViewProjMat, 
					   ShadowEffect* inShadowMapper);

	void RenderMeshWithShadowCube(D3DXMATRIXA16* inViewProjMat, 
								  ShadowEffect* inShadowMapper);
	void CleanUp();
	void SetWorldMatrix(D3DXMATRIXA16* _transform);
};
