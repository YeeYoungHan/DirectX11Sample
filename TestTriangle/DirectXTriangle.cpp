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

#include "stdafx.h"
#include "DirectXTriangle.h"

CDirectXTriangle::CDirectXTriangle()
{
}

CDirectXTriangle::~CDirectXTriangle()
{
}

bool CDirectXTriangle::CreateChild()
{
	// 삼각형 정점 정보
	Vertex arrTriangle[] =
	{
		{ XMFLOAT3( 0.0f, 0.25f, 0.0f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( 0.25f, -0.25f, 0.0f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.25f, -0.25f, 0.0f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) }
	};

	D3D11_BUFFER_DESC sttBD;
  
	sttBD.Usage = D3D11_USAGE_IMMUTABLE;
  sttBD.ByteWidth = sizeof(Vertex) * 3;
  sttBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  sttBD.CPUAccessFlags = 0;
  sttBD.MiscFlags = 0;
	sttBD.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA sttSRD;
  sttSRD.pSysMem = arrTriangle;
  
	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsVB ) );

	return true;
}

bool CDirectXTriangle::DrawChild()
{

	return true;
}
