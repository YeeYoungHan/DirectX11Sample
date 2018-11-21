/* 
 * Copyright (C) 2012 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#pragma once

#include "DirectX11.h"
#include "Light.h"
#include "RotationCameraPos.h"

/**
 * @ingroup TestGrid
 * @brief 정점 저장 구조체
 */
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Texture;
};

/**
 * @ingroup TestGrid
 * @brief 3D 큐브
 */
class CDirectXGrid : public CDirectX11
{
public:
	CDirectXGrid();
	~CDirectXGrid();

	virtual bool CreateChild();
	virtual bool DrawChild();

	bool Update();

	void OnMouseDown( HWND hWnd, int x, int y );
	void OnMouseUp( int x, int y );
	void OnMouseMove( HWND hWnd, int x, int y );

protected:
	CComPtr<ID3D11Buffer> m_pclsVB;
	CComPtr<ID3D11Buffer> m_pclsIB;
	CComPtr<ID3DX11Effect> m_pclsEffect;
	CComPtr<ID3D11ShaderResourceView> m_pclsShaderResView;

	ID3DX11EffectTechnique * m_pclsEffectTech;
	ID3DX11EffectMatrixVariable * m_pclsWorldViewProj;
	ID3DX11EffectMatrixVariable * m_pclsWorld;
	ID3DX11EffectMatrixVariable * m_pclsWorldInvTranspose;
	ID3DX11EffectVectorVariable * m_pclsEyePosW;
	ID3DX11EffectVariable * m_pclsDirectionalLight;
	ID3DX11EffectVariable * m_pclsMaterial;
	ID3DX11EffectShaderResourceVariable * m_pclsShaderResVar;
	ID3DX11EffectScalarVariable * m_pclsUseTexture;

	CComPtr<ID3D11InputLayout> m_pclsInputLayout;

	XMFLOAT4X4 m_arrCubeWorld[1];
	XMFLOAT4X4 m_sttView;
	XMFLOAT4X4 m_sttProj;

	XMFLOAT3	m_f3EyePos;

	CDirectionalLight	m_clsDirectionalLight;
	CMaterial m_clsMaterial;

	CRotationCameraPos	m_clsCamPos;
	POINT		m_sttMousePos;
	bool		m_bMouseDown;

	int			m_iIndexCount;
};

