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
#include "Effect.h"
#include "Figure.h"
#include "Light.h"
#include "RotationCameraPos.h"
#include "TetrisBlock.h"

/**
 * @ingroup Tetris
 * @brief 3D 기반 2차원 테트리스
 */
class CDirectXTetris : public CDirectX11
{
public:
	CDirectXTetris();
	~CDirectXTetris();

	virtual bool CreateChild();
	virtual bool DrawChild();

	bool Update();

	void OnMouseDown( HWND hWnd, int x, int y );
	void OnMouseUp( int x, int y );
	void OnMouseMove( HWND hWnd, int x, int y );

	void Rotate();
	void MoveRight( );
	void MoveLeft( );
	void MoveDown( );
	void ReStartGame( );

protected:
	void AddFixBlock( );
	void NewMoveBlock( );
	void DrawTetrisBlock( CTetrisBlock & clsBlock );
	E_COLLISION_TYPE CheckCollision( CTetrisBlock & clsBlock );

	CEffect m_clsEffect;
	CFigure m_clsBox[10];
	CComPtr<ID3D11ShaderResourceView> m_pclsShaderResView;

	XMFLOAT4X4 m_sttView;
	XMFLOAT4X4 m_sttProj;

	XMFLOAT3	m_f3EyePos;

	CRotationCameraPos	m_clsCamPos;
	POINT		m_sttMousePos;
	bool		m_bMouseDown;

	CTetrisBlock m_clsFixBlock;					// 고정된 블록 ( 움직이는 블록이 고정된 블록 또는 하단 벽에 충돌하면 고정된 블록에 포함된다. )
	CTetrisBlock m_clsMoveBlock;				// 움직이는 블록
	CTetrisBlock m_clsWallBlock;				// 좌/우/바닥 벽
	CTetrisBlock m_clsTopWallBlock;			// 상단 벽
	CTetrisBlock m_clsBottomWallBlock;	// 하단 벽 ( 충돌 처리를 위해서 하단 벽과 상단 벽을 구분하였다. )

	bool		m_bWork;
};

