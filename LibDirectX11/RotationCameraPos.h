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

#ifndef _ROTATION_CAMERA_POS_H_
#define _ROTATION_CAMERA_POS_H_

#include <d3dx11.h>
#include <xnamath.h>

#define MAX_XY_ANGLE (XM_PI / 2.0f - 0.01f)

/**
 * @ingroup LibDirectX11
 * @brief 회전 카메라 위치를 저장하는 클래스
 */
class CRotationCameraPos
{
public:
	CRotationCameraPos();
	~CRotationCameraPos();

	void Move( int iX, int iY );
	XMVECTOR GetVector();
	XMFLOAT3 GetEyePos();

private:
	float m_fDistance;	// 중앙에서 카메라까지의 거리
	float m_fXZAngle;		// 카메라가 중앙을 바로보는 위치에서 X축과 Z축 사이의 각도
	float m_fXYAngle;		// 카메라가 중앙을 바로보는 위치에서 X축과 Y축 사이의 각도
};

#endif
