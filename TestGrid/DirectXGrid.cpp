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
#include "DirectXGrid.h"
#include "trace.h"

CDirectXGrid::CDirectXGrid() : m_bMouseDown(false), m_iIndexCount(0)
{
	memset( &m_sttMousePos, 0, sizeof(m_sttMousePos) );
}

CDirectXGrid::~CDirectXGrid()
{
}

/**
 * @ingroup TestGrid
 * @brief 삼각형을 그리기 위한 준비 작업을 수행한다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXGrid::CreateChild()
{
	// 큐브 정점 정보
	Vertex arrCube[] =
	{
		// 앞면
		{ XMFLOAT3(  0.5,  0.5,  0.5 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 0
		{ XMFLOAT3(  0.5, -0.5,  0.5 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 1
		{ XMFLOAT3( -0.5, -0.5,  0.5 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 2
		{ XMFLOAT3( -0.5,  0.5,  0.5 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 3

		// 뒷면
		{ XMFLOAT3(  0.5,  0.5, -0.5 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 4
		{ XMFLOAT3(  0.5, -0.5, -0.5 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 5
		{ XMFLOAT3( -0.5, -0.5, -0.5 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 6
		{ XMFLOAT3( -0.5,  0.5, -0.5 ), XMFLOAT3( -1.0,  2.0, -1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 7

		// 왼쪽면
		{ XMFLOAT3( -0.5,  0.5,  0.5 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 8
		{ XMFLOAT3( -0.5, -0.5,  0.5 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 9
		{ XMFLOAT3( -0.5, -0.5, -0.5 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 10
		{ XMFLOAT3( -0.5,  0.5, -0.5 ), XMFLOAT3( -2.0,  1.0, -1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 11

		// 오른쪽면
		{ XMFLOAT3(  0.5,  0.5,  0.5 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 12
		{ XMFLOAT3(  0.5, -0.5,  0.5 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 13
		{ XMFLOAT3(  0.5, -0.5, -0.5 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 14
		{ XMFLOAT3(  0.5,  0.5, -0.5 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 15

		// 윗면
		{ XMFLOAT3(  0.5,  0.5,  0.5 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 16
		{ XMFLOAT3(  0.5,  0.5, -0.5 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 17
		{ XMFLOAT3( -0.5,  0.5, -0.5 ), XMFLOAT3( -1.0,  2.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 18
		{ XMFLOAT3( -0.5,  0.5,  0.5 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 19

		// 아랫면
		{ XMFLOAT3(  0.5, -0.5,  0.5 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 20
		{ XMFLOAT3(  0.5, -0.5, -0.5 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 21
		{ XMFLOAT3( -0.5, -0.5, -0.5 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 22
		{ XMFLOAT3( -0.5, -0.5,  0.5 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 1.0f, 0.0f ) }	// index 23
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
		8, 10, 9,
		8, 11, 10,

		// 오른쪽면
		12, 13, 14,
		12, 14, 15,

		// 윗면
		16, 17, 18,
		16, 18, 19,

		// 아랫면
		20, 22, 21,
		20, 23, 22
	};

	// 정점법선 벡터를 단위 벡터로 수정한다.
	int iVertexCount = _countof(arrCube);
	XMVECTOR vN;
		
	for( int i = 0; i < iVertexCount; ++i )
	{
		vN = XMLoadFloat3( &arrCube[i].Normal );
		vN = XMVector3Normalize( vN );
		XMStoreFloat3( &arrCube[i].Normal, vN );
	}

	m_iIndexCount = _countof(arrIndex);

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

	// 컴파일된 fx 파일을 로그한다.
	if( CreateEffect( "FX/texture.fxo", &m_pclsEffect ) == false ) return false;

	// fx 파일에 정의된 변수와 연결한다.
	m_pclsEffectTech = m_pclsEffect->GetTechniqueByName("ColorTech");
	m_pclsWorldViewProj = m_pclsEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_pclsWorld = m_pclsEffect->GetVariableByName("gWorld")->AsMatrix();
	m_pclsWorldInvTranspose = m_pclsEffect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_pclsEyePosW = m_pclsEffect->GetVariableByName("gEyePosW")->AsVector();
	m_pclsDirectionalLight = m_pclsEffect->GetVariableByName("gDirLight");
	m_pclsMaterial = m_pclsEffect->GetVariableByName("gMaterial");
	m_pclsShaderResVar = m_pclsEffect->GetVariableByName("gShaderResVar")->AsShaderResource();

	D3D11_INPUT_ELEMENT_DESC arrVertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCCORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DX11_PASS_DESC sttPassDesc;

	m_pclsEffectTech->GetPassByIndex(0)->GetDesc( &sttPassDesc );
	CHECK_FAILED( m_pclsDevice->CreateInputLayout( arrVertexDesc, 3, sttPassDesc.pIAInputSignature, sttPassDesc.IAInputSignatureSize, &m_pclsInputLayout ) );

	XMMATRIX sttI = XMMatrixIdentity();
	XMStoreFloat4x4( &m_sttView, sttI );

	// 5.6.3 카메라에 보이는 공간을 계산하기 위해서 원근 투영 변환이 필요하다.
	// 원근 투영 변환을 위해서 수직 시야각이 45도이고 종횡비가 1이며 가까운 평면은 z=1 이고 먼 평면은 z=1000 인 원근투영 행렬을 생성한다.
	XMMATRIX sttP = XMMatrixPerspectiveFovLH( 0.25f * XM_PI, 1.0f, 1.0f, 1000.0f );
	XMStoreFloat4x4( &m_sttProj, sttP );

	// 큐브 위치 저장
	XMStoreFloat4x4( &m_arrCubeWorld[0], XMMatrixTranslation( 0.0f, 0.0f, 0.0f ) );

	// 평행광 저장
	m_clsDirectionalLight.m_f4Ambient = XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f );
	m_clsDirectionalLight.m_f4Diffuse = XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f );
	m_clsDirectionalLight.m_f4Specular = XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f );
	m_clsDirectionalLight.m_f3Direction = XMFLOAT3( -0.5f, -0.5f, 0.5f );

	// 재질 저장
	m_clsMaterial.m_f4Ambient = XMFLOAT4( 0.93f, 0.9f, 0.86f, 1.0f );
	m_clsMaterial.m_f4Diffuse = XMFLOAT4( 0.93f, 0.9f, 0.86f, 1.0f );
	m_clsMaterial.m_f4Specular = XMFLOAT4( 0.93f, 0.9f, 0.86f, 100.0f );

	// 텍스처 이미지 파일을 로드한다.
	//CHECK_FAILED( D3DX11CreateShaderResourceViewFromFile( m_pclsDevice, L"Texture/box.png", 0, 0, &m_pclsShaderResView, 0 ) );

	return true;
}

/**
 * @ingroup TestGrid
 * @brief 삼각형을 화면에 그려준다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXGrid::DrawChild()
{
	m_pclsContext->IASetInputLayout( m_pclsInputLayout );

	UINT iStride = sizeof(Vertex);
	UINT iOffset = 0;

	m_pclsContext->IASetVertexBuffers( 0, 1, &(m_pclsVB.p), &iStride, &iOffset );
	m_pclsContext->IASetIndexBuffer( m_pclsIB.p, DXGI_FORMAT_R32_UINT, 0 );

	XMMATRIX view  = XMLoadFloat4x4( &m_sttView );
	XMMATRIX proj  = XMLoadFloat4x4( &m_sttProj );
	XMMATRIX world, worldViewProj;

	m_pclsDirectionalLight->SetRawValue( &m_clsDirectionalLight, 0, sizeof(m_clsDirectionalLight) );
	m_pclsEyePosW->SetRawValue( &m_f3EyePos, 0, sizeof(m_f3EyePos) );
	//m_pclsShaderResVar->SetResource( m_pclsShaderResView );

	D3DX11_TECHNIQUE_DESC sttTechDesc;
	m_pclsEffectTech->GetDesc( &sttTechDesc );

	for( UINT p = 0; p < sttTechDesc.Passes; ++p )
	{
		XMMATRIX world = XMLoadFloat4x4( &m_arrCubeWorld[0] ); 
		XMMATRIX worldViewProj = world * view * proj;

		XMMATRIX A = world;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);
		XMMATRIX worldInvTranspose = XMMatrixTranspose( XMMatrixInverse(&det, A) );

		m_pclsWorld->SetMatrix( (float*)&m_arrCubeWorld[0] );
		m_pclsWorldViewProj->SetMatrix( (float*)&worldViewProj );
		m_pclsWorldInvTranspose->SetMatrix( (float*)&worldInvTranspose );

		m_pclsMaterial->SetRawValue( &m_clsMaterial, 0, sizeof(m_clsMaterial) );

		m_pclsEffectTech->GetPassByIndex(p)->Apply( 0, m_pclsContext );
		m_pclsContext->DrawIndexed( m_iIndexCount, 0, 0 );
	}

	return true;
}

/**
 * @ingroup TestGrid
 * @brief 카메라 위치와 카메라가 큐브를 바라보는 방향을 이용하여서 View 행렬을 생성한다.
 * @returns true 를 리턴한다.
 */
bool CDirectXGrid::Update()
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

	// 카메라 위치를 저장한다.
	m_f3EyePos = m_clsCamPos.GetEyePos();
	
	return true;
}

/**
 * @ingroup TestGrid
 * @brief 마우스 버튼 down 이벤트 핸들러
 * @param hWnd	윈도우 핸들
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXGrid::OnMouseDown( HWND hWnd, int x, int y )
{
	m_sttMousePos.x = x;
	m_sttMousePos.y = y;
	m_bMouseDown = true;

	SetCapture( hWnd );
}

/**
 * @ingroup TestGrid
 * @brief 마우스 버튼 up 이벤트 핸들러
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXGrid::OnMouseUp( int x, int y )
{
	ReleaseCapture();
	m_bMouseDown = false;
}

/**
 * @ingroup TestGrid
 * @brief 마우스 이동 이벤트 핸들러
 * @param hWnd	윈도우 핸들
 * @param x			마우스 X 위치
 * @param y			마우스 Y 위치
 */
void CDirectXGrid::OnMouseMove( HWND hWnd, int x, int y )
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
