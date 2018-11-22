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

#include "Figure.h"
#include "check.h"

CFigure::CFigure() : m_iIndexCount(0)
{
}

CFigure::~CFigure()
{
}

bool CFigure::SetDevice( ID3D11Device * pclsDevice, ID3D11DeviceContext * pclsContext, CEffect * pclsEffect )
{
	m_pclsDevice = pclsDevice;
	m_pclsContext = pclsContext;
	m_pclsEffect = pclsEffect;

	return true;
}

bool CFigure::SetVertexIndex( VertexPosNormalTexture * parrVertex, int iVertexCount, UINT * parrIndex, int iIndexCount )
{
	// 정점 버퍼를 생성한다.
	D3D11_BUFFER_DESC sttBD;
  
	sttBD.Usage = D3D11_USAGE_IMMUTABLE;
	sttBD.ByteWidth = sizeof(VertexPosNormalTexture) * iVertexCount;
	sttBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sttBD.CPUAccessFlags = 0;
	sttBD.MiscFlags = 0;
	sttBD.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA sttSRD;
	sttSRD.pSysMem = parrVertex;
  
	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsVB ) );

	// 인덱스 버퍼를 생성한다.
	sttBD.ByteWidth = sizeof(UINT) * iIndexCount;
	sttBD.BindFlags = D3D11_BIND_INDEX_BUFFER;

	sttSRD.pSysMem = parrIndex;

	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsIB ) );
	m_iIndexCount = iIndexCount;

	// 입력 배치를 생성한다.
	D3D11_INPUT_ELEMENT_DESC arrVertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCCORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	if( m_pclsEffect->CreateInputLayout( arrVertexDesc, _countof(arrVertexDesc), &m_pclsInputLayout ) == false ) return false;

	return true;
}

bool CFigure::SetMaterial( CMaterial * pclsMaterial )
{
	m_clsMaterial = *pclsMaterial;

	return true;
}

bool CFigure::SetWorld( XMFLOAT4X4 * psttWorld )
{
	m_sttWorld = *psttWorld;

	return true;
}

bool CFigure::SetTexture( const TCHAR * pszFileName )
{
	CHECK_FAILED( D3DX11CreateShaderResourceViewFromFile( m_pclsDevice, pszFileName, 0, 0, &m_pclsShaderResView, 0 ) );

	return true;
}

bool CFigure::Draw( XMFLOAT4X4 * psttView, XMFLOAT4X4 * psttProj )
{
	m_pclsContext->IASetInputLayout( m_pclsInputLayout );

	UINT iStride = sizeof(VertexPosNormalTexture);
	UINT iOffset = 0;

	m_pclsContext->IASetVertexBuffers( 0, 1, &(m_pclsVB.p), &iStride, &iOffset );
	m_pclsContext->IASetIndexBuffer( m_pclsIB.p, DXGI_FORMAT_R32_UINT, 0 );

	XMMATRIX view  = XMLoadFloat4x4( psttView );
	XMMATRIX proj  = XMLoadFloat4x4( psttProj );
	XMMATRIX world = XMLoadFloat4x4( &m_sttWorld ); 
	XMMATRIX worldViewProj = world * view * proj;

	XMMATRIX A = world;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX worldInvTranspose = XMMatrixTranspose( XMMatrixInverse(&det, A) );

	m_pclsEffect->SetWorld( &m_sttWorld, &worldViewProj, &worldInvTranspose );
	m_pclsEffect->SetMaterial( &m_clsMaterial );
	m_pclsEffect->SetShaderResourceView( m_pclsShaderResView );

	int iPassCount = m_pclsEffect->GetPassCount();

	for( int p = 0; p < iPassCount; ++p )
	{
		m_pclsEffect->Apply( p );
		m_pclsContext->DrawIndexed( m_iIndexCount, 0, 0 );
	}

	return true;
}
