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
#include "d3dx11effect.h"
#include "Light.h"
#include "Effect.h"

struct VertexPosNormalTexture
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Texture;
};

class CFigure
{
public:
	CFigure();
	~CFigure();

	bool SetDevice( ID3D11Device * pclsDevice, ID3D11DeviceContext * pclsContext, CEffect * pclsEffect );
	bool SetVertexIndex( VertexPosNormalTexture * parrVertex, int iVertexCount, UINT * parrIndex, int iIndexCount );
	bool SetMaterial( CMaterial * pclsMaterial );
	bool SetWorld( XMFLOAT4X4 * psttWorld );
	bool SetTexture( const TCHAR * pszFileName );

	bool Draw( XMFLOAT4X4 * psttView, XMFLOAT4X4 * psttProj );

private:
	ID3D11Device * m_pclsDevice;
	ID3D11DeviceContext * m_pclsContext;
	CEffect * m_pclsEffect;
	
public:
	CComPtr<ID3D11Buffer> m_pclsVB;
	CComPtr<ID3D11Buffer> m_pclsIB;

	CComPtr<ID3D11InputLayout> m_pclsInputLayout;
	CComPtr<ID3D11ShaderResourceView> m_pclsShaderResView;

	CMaterial m_clsMaterial;

	XMFLOAT4X4 m_sttWorld;

	int		m_iIndexCount;
};
