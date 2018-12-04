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

#define BOX_WIDTH	0.16f

enum BOX_COLOR
{
	BC_BLUE = 0,
	BC_GREEN,
	BC_ORANGE,
	BC_RED,
	BC_SKYBLUE,
	BC_VILOET,
	BC_YELLOW
};

/**
 * @ingroup TestGrid
 * @brief 3D Å¥ºê
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

protected:
	CEffect m_clsEffect;
	CFigure m_clsBox[7];
	CFigure m_clsBoxWall;
	CComPtr<ID3D11ShaderResourceView> m_pclsShaderResView;

	XMFLOAT4X4 m_sttView;
	XMFLOAT4X4 m_sttProj;

	XMFLOAT3	m_f3EyePos;

	CRotationCameraPos	m_clsCamPos;
	POINT		m_sttMousePos;
	bool		m_bMouseDown;
};

