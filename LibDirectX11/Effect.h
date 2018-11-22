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

#include <atlbase.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "d3dx11effect.h"
#include "Light.h"

class CEffect
{
public:
	CEffect();
	~CEffect();

	bool Create( ID3D11Device * pclsDevice, ID3D11DeviceContext * pclsContext, const char * pszFileName );
	bool CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC * parrVertexDesc, int iVertexDescCount, ID3D11InputLayout ** pclsInputLayout );

	bool SetWorld( XMFLOAT4X4 * psttWorld, XMMATRIX * psttWorldViewProj, XMMATRIX * psttWorldInvTranspose );
	bool SetShaderResourceView( ID3D11ShaderResourceView * pclsShaderResView );
	bool SetMaterial( CMaterial * pclsMaterial );
	bool SetDirectionalLight( CDirectionalLight * pclsDirectionalLight );
	bool SetEyePos( XMFLOAT3 * psttEyePos );

	bool Apply( int iPassIndex );

	int GetPassCount();

private:
	bool CreateEffect( const char * pszFxoFile, ID3DX11Effect ** ppclsEffect );

	ID3D11Device * m_pclsDevice;
	ID3D11DeviceContext * m_pclsContext;

public:
	CComPtr<ID3DX11Effect> m_pclsEffect;

	ID3DX11EffectTechnique * m_pclsEffectTech;
	ID3DX11EffectMatrixVariable * m_pclsWorldViewProj;
	ID3DX11EffectMatrixVariable * m_pclsWorld;
	ID3DX11EffectMatrixVariable * m_pclsWorldInvTranspose;
	ID3DX11EffectVectorVariable * m_pclsEyePosW;
	ID3DX11EffectVariable * m_pclsDirectionalLight;
	ID3DX11EffectVariable * m_pclsMaterial;
	ID3DX11EffectShaderResourceVariable * m_pclsShaderResVar;
	ID3DX11EffectScalarVariable * m_pclsUseTexture;
};
