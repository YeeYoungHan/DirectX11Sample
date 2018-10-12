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
#include "DirectXCube.h"

CDirectXCube::CDirectXCube() : m_fTheta(2.25f * XM_PI), m_fPhi(XM_PIDIV4), m_fRadius(3.0f)
{
}

CDirectXCube::~CDirectXCube()
{
}

/**
 * @ingroup TestTriangle
 * @brief 삼각형을 그리기 위한 준비 작업을 수행한다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXCube::CreateChild()
{
	// 큐브 정점 정보
	Vertex arrCube[] =
	{
		// 앞면 (빨간색)
		{ XMFLOAT3(  0.5f,  0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ) },
		
		// 뒷면 (노랑색)
		{ XMFLOAT3(  0.5f,  0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f, -0.5f ), XMFLOAT4( 1.0f, 1.0f, 0.0f, 1.0f ) },

		// 왼쪽 면 (파랑색)
		{ XMFLOAT3( -0.5f,  0.5f,  0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f,  0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f,  0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f, -0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f ) },

		// 오른쪽 면 (보라색)
		{ XMFLOAT3(  0.5f,  0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f, -0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f, -0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f,  0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f, -0.5f ), XMFLOAT4( 1.0f, 0.0f, 1.0f, 1.0f ) },

		// 윗면 (녹색)
		{ XMFLOAT3(  0.5f,  0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f,  0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f,  0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f ) },

		// 아랫면 (하늘색)
		{ XMFLOAT3(  0.5f, -0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3(  0.5f, -0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f,  0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) },
		{ XMFLOAT3( -0.5f, -0.5f, -0.5f ), XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ) }
	};

	// 정점 버퍼를 생성한다.
	D3D11_BUFFER_DESC sttBD;
  
	sttBD.Usage = D3D11_USAGE_IMMUTABLE;
  sttBD.ByteWidth = sizeof(Vertex) * 36;
  sttBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  sttBD.CPUAccessFlags = 0;
  sttBD.MiscFlags = 0;
	sttBD.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA sttSRD;
  sttSRD.pSysMem = arrCube;
  
	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsVB ) );

	// 
	if( CreateEffect( "FX/color.fxo", &m_pclsEffect ) == false ) return false;

	m_pclsEffectTech = m_pclsEffect->GetTechniqueByName("ColorTech");
	m_pclsWorldViewProj = m_pclsEffect->GetVariableByName("gWorldViewProj")->AsMatrix();

	D3D11_INPUT_ELEMENT_DESC arrVertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DX11_PASS_DESC sttPassDesc;

	m_pclsEffectTech->GetPassByIndex(0)->GetDesc( &sttPassDesc );
	CHECK_FAILED( m_pclsDevice->CreateInputLayout( arrVertexDesc, 2, sttPassDesc.pIAInputSignature, sttPassDesc.IAInputSignatureSize, &m_pclsInputLayout ) );

	XMMATRIX sttI = XMMatrixIdentity();
	XMStoreFloat4x4( &m_sttWorld, sttI );
	XMStoreFloat4x4( &m_sttView, sttI );
	XMStoreFloat4x4( &m_sttProj, sttI );

	return true;
}

/**
 * @ingroup TestTriangle
 * @brief 삼각형을 화면에 그려준다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXCube::DrawChild()
{
	m_pclsContext->IASetInputLayout( m_pclsInputLayout );

	UINT iStride = sizeof(Vertex);
  UINT iOffset = 0;

  m_pclsContext->IASetVertexBuffers( 0, 1, &(m_pclsVB.p), &iStride, &iOffset );

	XMMATRIX world = XMLoadFloat4x4( &m_sttWorld );
	XMMATRIX view  = XMLoadFloat4x4( &m_sttView );
	XMMATRIX proj  = XMLoadFloat4x4( &m_sttProj );
	XMMATRIX worldViewProj = world * view * proj;

	m_pclsWorldViewProj->SetMatrix( reinterpret_cast<float*>(&worldViewProj) );

	D3DX11_TECHNIQUE_DESC sttTechDesc;
	m_pclsEffectTech->GetDesc( &sttTechDesc );

	for( UINT p = 0; p < sttTechDesc.Passes; ++p )
	{
		m_pclsEffectTech->GetPassByIndex(p)->Apply( 0, m_pclsContext );
		m_pclsContext->Draw( 36, 0 );
	}

	return true;
}

bool CDirectXCube::Update()
{
	float x = m_fRadius * sinf( m_fPhi ) * cosf( m_fTheta );
	float z = m_fRadius * sinf( m_fPhi ) * sinf( m_fTheta );
	float y = m_fRadius * cosf( m_fPhi );

	// 카메라 위치
	XMVECTOR pos = XMVectorSet( x, y, z, 1.0f );

	// 큐브 위치
	XMVECTOR target = XMVectorZero();

	// 카메라가 타겟을 바라볼 때의 위쪽 방향.
	XMVECTOR up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );

	// 카메라 위치와 카메라가 큐브를 바라보는 방향을 이용하여서 View 행렬을 생성한다.
	XMMATRIX view = XMMatrixLookAtLH( pos, target, up );

	XMStoreFloat4x4( &m_sttView, view );

	return true;
}