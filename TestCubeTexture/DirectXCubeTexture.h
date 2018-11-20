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
#include "trace.h"

#define MAX_XY_ANGLE (XM_PI / 2.0f - 0.01f)

/**
 * @ingroup TestCubeTexture
 * @brief 정점 저장 구조체
 */
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Texture;
};

/**
 * @ingroup TestCubeTexture
 * @brief 카메라 위치를 저장하는 클래스
 */
class CCamPos
{
public:
	CCamPos() : m_fDistance(5.0), m_fXZAngle(0.0), m_fXYAngle(0.0)
	{}

	/**
	 * @ingroup TestCubeTexture
	 * @brief 카메라 위치를 수정한다.
	 * @param iX X 축 이동 거리
	 * @param iY Y 축 이동 거리
	 */
	void Move( int iX, int iY )
	{
		m_fXZAngle += iX * XM_PI / 400;
		m_fXYAngle += iY * XM_PI / 400;

		// 2PI 를 초과하면 2PI 이하로 수정한다.
		if( m_fXZAngle > XM_2PI )
		{
			m_fXZAngle -= XM_2PI;
		}
		else if( m_fXZAngle < ((-1)*XM_2PI) )
		{
			m_fXZAngle += XM_2PI;
		}

		// 2/PI 를 초과하면 카메라의 X 위치가 마이너스가 되어야 하므로 2/PI 를 초과하지 못 한다.
		if( m_fXYAngle > MAX_XY_ANGLE )
		{
			m_fXYAngle = MAX_XY_ANGLE;
		}
		else if( m_fXYAngle < ((-1) * MAX_XY_ANGLE) )
		{
			m_fXYAngle = (-1) * MAX_XY_ANGLE;
		}

		TRACE( "XZ(%.2f) XY(%.2f)\n", m_fXZAngle, m_fXYAngle );
	}

	/**
	 * @ingroup TestCubeTexture
	 * @brief 카메라 위치를 저장한 VECTOR 를 리턴한다.
	 * @returns 카메라 위치를 저장한 VECTOR 를 리턴한다.
	 */
	XMVECTOR GetVector()
	{
		XMVECTOR clsVec;

		clsVec.m128_f32[0] = m_fDistance * cos(m_fXYAngle) * cos(m_fXZAngle);
		clsVec.m128_f32[1] = m_fDistance * sin(m_fXYAngle);
		clsVec.m128_f32[2] = m_fDistance * cos(m_fXYAngle) * sin(m_fXZAngle);
		clsVec.m128_f32[3] = 1.0;

		return clsVec;
	}

	XMFLOAT3 GetEyePos()
	{
		XMVECTOR clsVec = GetVector();
		XMFLOAT3 f3EyePos = XMFLOAT3( clsVec.m128_f32[0], clsVec.m128_f32[1], clsVec.m128_f32[2] );

		return f3EyePos;
	}

	float m_fDistance;	// 중앙에서 카메라까지의 거리
	float m_fXZAngle;		// 카메라가 중앙을 바로보는 위치에서 X축과 Z축 사이의 각도
	float m_fXYAngle;		// 카메라가 중앙을 바로보는 위치에서 X축과 Y축 사이의 각도
};

class CDirectionalLight
{
public:
	CDirectionalLight()
	{
		memset( this, 0, sizeof(CDirectionalLight) );
	}

	XMFLOAT4 m_f4Ambient;
	XMFLOAT4 m_f4Diffuse;
	XMFLOAT4 m_f4Specular;
	XMFLOAT3 m_f3Direction;
	float		 m_fPad;
};

class CMaterial
{
public:
	CMaterial()
	{
		memset( this, 0, sizeof(CMaterial) );
	}

	XMFLOAT4 m_f4Ambient;
	XMFLOAT4 m_f4Diffuse;
	XMFLOAT4 m_f4Specular; // w = SpecPower
	XMFLOAT4 m_f4Reflect;
};

/**
 * @ingroup TestCubeTexture
 * @brief 3D 큐브
 */
class CDirectXCubeTexture : public CDirectX11
{
public:
	CDirectXCubeTexture();
	~CDirectXCubeTexture();

	virtual bool CreateChild();
	virtual bool DrawChild();

	bool Update();

	void OnMouseDown( HWND hWnd, int x, int y );
	void OnMouseUp( int x, int y );
	void OnMouseMove( HWND hWnd, int x, int y );

protected:
	CComPtr<ID3D11Buffer> m_pclsVB;
	CComPtr<ID3D11Buffer> m_pclsIB;
	CComPtr<ID3DX11Effect> m_pclsEffect;
	CComPtr<ID3D11ShaderResourceView> m_pclsShaderResView;

	ID3DX11EffectTechnique * m_pclsEffectTech;
	ID3DX11EffectMatrixVariable * m_pclsWorldViewProj;
	ID3DX11EffectMatrixVariable * m_pclsWorld;
	ID3DX11EffectMatrixVariable * m_pclsWorldInvTranspose;
	ID3DX11EffectVectorVariable * m_pclsEyePosW;
	ID3DX11EffectVariable * m_pclsDirectionalLight;
	ID3DX11EffectVariable * m_pclsMaterial;
	ID3DX11EffectShaderResourceVariable * m_pclsShaderResVar;

	CComPtr<ID3D11InputLayout> m_pclsInputLayout;

	XMFLOAT4X4 m_arrCubeWorld[1];
	XMFLOAT4X4 m_sttView;
	XMFLOAT4X4 m_sttProj;

	XMFLOAT3	m_f3EyePos;

	CDirectionalLight	m_clsDirectionalLight;
	CMaterial m_clsMaterial;

	CCamPos	m_clsCamPos;
	POINT		m_sttMousePos;
	bool		m_bMouseDown;

	int			m_iIndexCount;
};

