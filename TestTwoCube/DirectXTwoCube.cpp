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
#include "DirectXTwoCube.h"
#include "trace.h"

CDirectXTwoCube::CDirectXTwoCube() : m_bMouseDown(false), m_iIndexCount(0)
{
	memset( &m_sttMousePos, 0, sizeof(m_sttMousePos) );
}

CDirectXTwoCube::~CDirectXTwoCube()
{
}

/**
 * @ingroup TestTwoCube
 * @brief 삼각형을 그리기 위한 준비 작업을 수행한다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXTwoCube::CreateChild()
{
	// 큐브 정점 정보
	Vertex arrCube[] =
	{
		{ XMFLOAT3(  0.5,  0.5,  0.5 ), XMFLOAT4( 1.0, 0.0, 0.0, 1.0 ) },	// index 0
		{ XMFLOAT3(  0.5, -0.5,  0.5 ), XMFLOAT4( 0.0, 1.0, 0.0, 1.0 ) },	// index 1
		{ XMFLOAT3( -0.5, -0.5,  0.5 ), XMFLOAT4( 0.0, 0.0, 1.0, 1.0 ) },	// index 2
		{ XMFLOAT3( -0.5,  0.5,  0.5 ), XMFLOAT4( 1.0, 1.0, 0.0, 1.0 ) },	// index 3
		{ XMFLOAT3(  0.5,  0.5, -0.5 ), XMFLOAT4( 1.0, 0.0, 1.0, 1.0 ) },	// index 4
		{ XMFLOAT3(  0.5, -0.5, -0.5 ), XMFLOAT4( 0.0, 1.0, 1.0, 1.0 ) },	// index 5
		{ XMFLOAT3( -0.5, -0.5, -0.5 ), XMFLOAT4( 0.5, 0.5, 0.0, 1.0 ) },	// index 6
		{ XMFLOAT3( -0.5,  0.5, -0.5 ), XMFLOAT4( 0.0, 0.5, 0.5, 1.0 ) },	// index 7
	};

	UINT arrIndex[] =
	{
		// 앞면
		0, 2, 1,
		0, 3, 2,

		// 뒷면
		4, 6, 7,
		4, 5, 6,

		// 왼쪽면
		3, 6, 2,
		3, 7, 6,

		// 오른쪽면
		0, 1, 5,
		0, 5, 4,

		// 윗면
		0, 4, 7,
		0, 7, 3,

		// 아랫면
		1, 6, 5,
		1, 2, 6
	};

	// 정점 버퍼를 생성한다.
	D3D11_BUFFER_DESC sttBD;
  
	sttBD.Usage = D3D11_USAGE_IMMUTABLE;
	sttBD.ByteWidth = sizeof(arrCube);
	sttBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sttBD.CPUAccessFlags = 0;
	sttBD.MiscFlags = 0;
	sttBD.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA sttSRD;
	sttSRD.pSysMem = arrCube;
  
	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsVB ) );

	// 인덱스 버퍼를 생성한다.
	sttBD.ByteWidth = sizeof(arrIndex);
	sttBD.BindFlags = D3D11_BIND_INDEX_BUFFER;

	sttSRD.pSysMem = arrIndex;

	CHECK_FAILED( m_pclsDevice->CreateBuffer( &sttBD, &sttSRD, &m_pclsIB ) );
	m_iIndexCount = _countof(arrIndex);

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
	XMStoreFloat4x4( &m_sttView, sttI );

	// 5.6.3 카메라에 보이는 공간을 계산하기 위해서 원근 투영 변환이 필요하다.
	// 원근 투영 변환을 위해서 수직 시야각이 45도이고 종횡비가 1이며 가까운 평면은 z=1 이고 먼 평면은 z=1000 인 원근투영 행렬을 생성한다.
	XMMATRIX sttP = XMMatrixPerspectiveFovLH( 0.25f * XM_PI, 1.0f, 1.0f, 1000.0f );
	XMStoreFloat4x4( &m_sttProj, sttP );

	// 2개의 큐브 위치 저장
	XMStoreFloat4x4( &m_arrCubeWorld[0], XMMatrixTranslation( 0.7f, 0.7f, 0.7f ) );
	XMStoreFloat4x4( &m_arrCubeWorld[1], XMMatrixTranslation( -0.7f, -0.7f, -0.7f ) );

	return true;
}

/**
 * @ingroup TestTwoCube
 * @brief 삼각형을 화면에 그려준다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXTwoCube::DrawChild()
{
	m_pclsContext->IASetInputLayout( m_pclsInputLayout );

	UINT iStride = sizeof(Vertex);
	UINT iOffset = 0;

	m_pclsContext->IASetVertexBuffers( 0, 1, &(m_pclsVB.p), &iStride, &iOffset );
	m_pclsContext->IASetIndexBuffer( m_pclsIB.p, DXGI_FORMAT_R32_UINT, 0 );

	XMMATRIX view  = XMLoadFloat4x4( &m_sttView );
	XMMATRIX proj  = XMLoadFloat4x4( &m_sttProj );
	XMMATRIX world, worldViewProj;
	
	D3DX11_TECHNIQUE_DESC sttTechDesc;
	m_pclsEffectTech->GetDesc( &sttTechDesc );

	for( UINT p = 0; p < sttTechDesc.Passes; ++p )
	{
		for( int i = 0; i < 2; ++i )
		{
			XMMATRIX world = XMLoadFloat4x4( &m_arrCubeWorld[i] );
			XMMATRIX worldViewProj = world * view * proj;

			m_pclsWorldViewProj->SetMatrix( reinterpret_cast<float*>(&worldViewProj) );
			m_pclsEffectTech->GetPassByIndex(p)->Apply( 0, m_pclsContext );
			m_pclsContext->DrawIndexed( m_iIndexCount, 0, 0 );
		}
	}

	return true;
}

/**
 * @ingroup TestTwoCube
 * @brief 카메라 위치와 카메라가 큐브를 바라보는 방향을 이용하여서 View 행렬을 생성한다.
 * @returns true 를 리턴한다.
 */
bool CDirectXTwoCube::Update()
{
	// 5.6.2 세계 공간에서 시야 공간으로 좌표 변환 변경을 위한 시야 행렬을 생성한다.
	XMVECTOR pos = m_clsCamPos.GetVector();
	TRACE( "x(%.2f) y(%.2f) z(%.2f)\n", pos.m128_f32[0], pos.m128_f32[1], pos.m128_f32[2] );

	// 큐브 위치
	XMVECTOR target = XMVectorZero();

	// 카메라가 타겟을 바라볼 때의 위쪽 방향.
	XMVECTOR up = XMVectorSet( 0.0, 1.0, 0.0, 0.0 );

	// 카메라 위치와 카메라가 큐브를 바라보는 방향을 이용하여서 View 행렬을 생성한다.
	XMMATRIX view = XMMatrixLookAtLH( pos, target, up );

	XMStoreFloat4x4( &m_sttView, view );

	return true;
}

/**
 * @ingroup TestTwoCube
 * @brief 마우스 버튼 down 이벤트 핸들러
 * @param hWnd	윈도우 핸들
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXTwoCube::OnMouseDown( HWND hWnd, int x, int y )
{
	m_sttMousePos.x = x;
	m_sttMousePos.y = y;
	m_bMouseDown = true;

	SetCapture( hWnd );
}

/**
 * @ingroup TestTwoCube
 * @brief 마우스 버튼 up 이벤트 핸들러
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXTwoCube::OnMouseUp( int x, int y )
{
	ReleaseCapture();
	m_bMouseDown = false;
}

/**
 * @ingroup TestTwoCube
 * @brief 마우스 이동 이벤트 핸들러
 * @param hWnd	윈도우 핸들
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXTwoCube::OnMouseMove( HWND hWnd, int x, int y )
{
	if( m_bMouseDown )
	{
		m_clsCamPos.Move( x - m_sttMousePos.x, y - m_sttMousePos.y );

		m_sttMousePos.x = x;
		m_sttMousePos.y = y;

		Update();
		Draw();
	}
}
