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

#include "RotationCameraPos.h"
#include "trace.h"

CRotationCameraPos::CRotationCameraPos() : m_fDistance(5.0), m_fXZAngle(0.0), m_fXYAngle(0.0)
{
}

CRotationCameraPos::~CRotationCameraPos()
{
}

/**
 * @ingroup LibDirectX11
 * @brief 카메라 위치를 수정한다.
 * @param iX X 축 이동 거리
 * @param iY Y 축 이동 거리
 */
void CRotationCameraPos::Move( int iX, int iY )
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
 * @ingroup LibDirectX11
 * @brief 카메라 위치를 저장한 VECTOR 를 리턴한다.
 * @returns 카메라 위치를 저장한 VECTOR 를 리턴한다.
 */
XMVECTOR CRotationCameraPos::GetVector()
{
	XMVECTOR clsVec;

	clsVec.m128_f32[0] = m_fDistance * cos(m_fXYAngle) * cos(m_fXZAngle);
	clsVec.m128_f32[1] = m_fDistance * sin(m_fXYAngle);
	clsVec.m128_f32[2] = m_fDistance * cos(m_fXYAngle) * sin(m_fXZAngle);
	clsVec.m128_f32[3] = 1.0;

	return clsVec;
}

XMFLOAT3 CRotationCameraPos::GetEyePos()
{
	XMVECTOR clsVec = GetVector();
	XMFLOAT3 f3EyePos = XMFLOAT3( clsVec.m128_f32[0], clsVec.m128_f32[1], clsVec.m128_f32[2] );

	return f3EyePos;
}
