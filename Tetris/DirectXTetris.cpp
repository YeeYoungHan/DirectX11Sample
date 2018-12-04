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
#include "DirectXTetris.h"
#include "trace.h"
#include "check.h"

CDirectXTetris::CDirectXTetris() : m_bMouseDown(false)
{
	memset( &m_sttMousePos, 0, sizeof(m_sttMousePos) );
}

CDirectXTetris::~CDirectXTetris()
{
}

/**
 * @ingroup TestGrid
 * @brief 삼각형을 그리기 위한 준비 작업을 수행한다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXTetris::CreateChild()
{
	// 큐브 정점 정보
	VertexPosNormalTexture arrCube[] =
	{
		// 앞면
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 0
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 1
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 2
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 3

		// 뒷면
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 4
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 5
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 6
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -1.0,  2.0, -1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 7

		// 왼쪽면
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 8
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 9
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 10
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -2.0,  1.0, -1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 11

		// 오른쪽면
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 12
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 13
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 14
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 15

		// 윗면
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0,  1.0 ), XMFLOAT2( 1.0f, 0.0f ) },	// index 16
		{ XMFLOAT3(  BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  1.0,  1.0, -2.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 17
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -1.0,  2.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 18
		{ XMFLOAT3( -BOX_WIDTH/2,  BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -2.0,  1.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 19

		// 아랫면
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3(  1.0, -2.0,  1.0 ), XMFLOAT2( 0.0f, 0.0f ) },	// index 20
		{ XMFLOAT3(  BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3(  2.0, -1.0, -1.0 ), XMFLOAT2( 0.0f, 1.0f ) },	// index 21
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2, -BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0, -1.0 ), XMFLOAT2( 1.0f, 1.0f ) },	// index 22
		{ XMFLOAT3( -BOX_WIDTH/2, -BOX_WIDTH/2,  BOX_WIDTH/2 ), XMFLOAT3( -1.0, -1.0,  2.0 ), XMFLOAT2( 1.0f, 0.0f ) }	// index 23
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

	// 컴파일된 fx 파일을 로그한다.
	if( m_clsEffect.Create( m_pclsDevice, m_pclsContext, "FX/texture.fxo" ) == false ) return false;

	for( int i = 0; i < 9; ++i )
	{
		m_clsBox[i].SetDevice( m_pclsDevice, m_pclsContext, &m_clsEffect );
		m_clsBox[i].SetVertexIndex( arrCube, _countof(arrCube), arrIndex, _countof(arrIndex) );
	}

	// 5.6.3 카메라에 보이는 공간을 계산하기 위해서 원근 투영 변환이 필요하다.
	// 원근 투영 변환을 위해서 수직 시야각이 45도이고 종횡비가 1이며 가까운 평면은 z=1 이고 먼 평면은 z=1000 인 원근투영 행렬을 생성한다.
	XMMATRIX sttP = XMMatrixPerspectiveFovLH( 0.25f * XM_PI, 1.0f, 1.0f, 1000.0f );
	XMStoreFloat4x4( &m_sttProj, sttP );

	m_clsBox[0].SetTexture( _T("Texture/box_blue.png") );
	m_clsBox[1].SetTexture( _T("Texture/box_green.png") );
	m_clsBox[2].SetTexture( _T("Texture/box_orange.png") );
	m_clsBox[3].SetTexture( _T("Texture/box_red.png") );
	m_clsBox[4].SetTexture( _T("Texture/box_skyblue.png") );
	m_clsBox[5].SetTexture( _T("Texture/box_violet.png") );
	m_clsBox[6].SetTexture( _T("Texture/box_yellow.png") );
	m_clsBox[7].SetTexture( _T("Texture/box_gray.jpg") );
	m_clsBox[8].SetTexture( _T("Texture/box_gray.jpg") );

	m_clsWallBlock.Create( BC_BLACK );
	m_clsTopWallBlock.Create( BC_BLACK_TOP );
	m_clsMoveBlock.Create( BC_VILOET );

	return true;
}

/**
 * @ingroup TestGrid
 * @brief 삼각형을 화면에 그려준다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectXTetris::DrawChild()
{
	m_clsEffect.SetEyePos( &m_f3EyePos );

	/*
	// 상단/하단 테두리
	for( int i = 0; i < 12; ++i )
	{
		m_clsBoxWall.SetWorld( 0, BOX_WIDTH * 11, -BOX_WIDTH * 6 + i * BOX_WIDTH );
		m_clsBoxWall.Draw( &m_sttView, &m_sttProj );

		m_clsBoxWall.SetWorld( 0, -BOX_WIDTH * 10, -BOX_WIDTH * 6 + i * BOX_WIDTH );
		m_clsBoxWall.Draw( &m_sttView, &m_sttProj );
	}

	// 좌/우 테두리
	for( int i = 0; i < 20; ++i )
	{
		m_clsBoxWall.SetWorld( 0, -BOX_WIDTH * 9 + i * BOX_WIDTH, -BOX_WIDTH * 6 );
		m_clsBoxWall.Draw( &m_sttView, &m_sttProj );

		m_clsBoxWall.SetWorld( 0, -BOX_WIDTH * 9 + i * BOX_WIDTH, BOX_WIDTH * 5 );
		m_clsBoxWall.Draw( &m_sttView, &m_sttProj );
	}
	*/

	DrawTetrisBlock( m_clsWallBlock );
	DrawTetrisBlock( m_clsTopWallBlock );
	DrawTetrisBlock( m_clsFixBlock );
	DrawTetrisBlock( m_clsMoveBlock );

	return true;
}

/**
 * @ingroup TestGrid
 * @brief 카메라 위치와 카메라가 큐브를 바라보는 방향을 이용하여서 View 행렬을 생성한다.
 * @returns true 를 리턴한다.
 */
bool CDirectXTetris::Update()
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
void CDirectXTetris::OnMouseDown( HWND hWnd, int x, int y )
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
void CDirectXTetris::OnMouseUp( int x, int y )
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
void CDirectXTetris::OnMouseMove( HWND hWnd, int x, int y )
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

void CDirectXTetris::Rotate()
{
	m_clsMoveBlock.Rotate();
	Draw();
}

void CDirectXTetris::MoveRight( )
{
	CTetrisBlock clsBlock = m_clsMoveBlock;
	clsBlock.MoveRight();
	E_COLLISION_TYPE eType = CheckCollision( clsBlock );

	if( eType == CT_NULL )
	{
		m_clsMoveBlock.MoveRight();
		Draw();
	}
	else if( eType == CT_BOTTOM )
	{

	}
}

void CDirectXTetris::MoveLeft( )
{
	CTetrisBlock clsBlock = m_clsMoveBlock;
	clsBlock.MoveLeft();
	E_COLLISION_TYPE eType = CheckCollision( clsBlock );

	if( eType == CT_NULL )
	{
		m_clsMoveBlock.MoveLeft();
		Draw();
	}
	else if( eType == CT_BOTTOM )
	{

	}
}

void CDirectXTetris::DrawTetrisBlock( CTetrisBlock & clsBlock )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;
	TETRIS_BLOCK_PART_LIST * pclsList = clsBlock.GetList();

	for( itPL = pclsList->begin(); itPL != pclsList->end(); ++itPL )
	{
		m_clsBox[itPL->m_eColor].SetWorld( 0, itPL->GetY(), itPL->GetZ() );
		m_clsBox[itPL->m_eColor].Draw( &m_sttView, &m_sttProj );
	}
}

E_COLLISION_TYPE CDirectXTetris::CheckCollision( CTetrisBlock & clsBlock )
{
	E_COLLISION_TYPE eType = CT_NULL;

	eType = m_clsFixBlock.CheckCollision( clsBlock );
	if( eType != CT_NULL ) return eType;

	eType = m_clsWallBlock.CheckCollision( clsBlock );
	if( eType != CT_NULL ) return eType;

	return eType;
}
