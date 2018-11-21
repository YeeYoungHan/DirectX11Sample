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

struct VertexPosNormalTexture
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Texture;
};

class CFigure
{
public:
	CFigure( ID3D11Device * pclsDevice );
	~CFigure();

	bool SetVertexIndex( VertexPosNormalTexture * parrVertex, int iVertexCount, UINT * parrIndex, int iIndexCount );

private:
	CComPtr<ID3D11Device> m_pclsDevice;
	CComPtr<ID3D11Buffer> m_pclsVB;
	CComPtr<ID3D11Buffer> m_pclsIB;
};
