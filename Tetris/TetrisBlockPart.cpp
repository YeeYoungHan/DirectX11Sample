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
#include "TetrisBlock.h"
#include "trace.h"

CTetrisBlockPart::CTetrisBlockPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor ) : m_fLocalY(fLocalY), m_fLocalZ(fLocalZ), m_fWorldY(0.0f), m_fWorldZ(0.0f), m_eColor(eColor)
{
}

/**
 * @ingroup Tetris
 * @brief 입력된 fY 만큼 Y 축으로 이동하고 입력된 fZ 만큼 Z 축으로 이동한다.
 * @param fY	Y 축으로 이동할 값
 * @param fZ	Z 축으로 이동할 값
 */
void CTetrisBlockPart::Move( float fY, float fZ )
{
	m_fWorldY += fY;
	m_fWorldZ += fZ;
}

/**
 * @ingroup Tetris
 * @brief 회전한다.
 */
void CTetrisBlockPart::Rotate()
{
	float fTemp = m_fLocalY;
	m_fLocalY = m_fLocalZ;
	m_fLocalZ = fTemp;

	m_fLocalZ *= -1;
}

/**
 * @ingroup Tetris
 * @brief 현재 Y 값을 리턴한다.
 * @returns 현재 Y 값을 리턴한다.
 */
float CTetrisBlockPart::GetY() const
{
	return m_fWorldY + m_fLocalY;
}

/**
 * @ingroup Tetris
 * @brief 현재 Z 값을 리턴한다.
 * @returns 현재 Z 값을 리턴한다.
 */
float CTetrisBlockPart::GetZ() const
{
	return m_fWorldZ + m_fLocalZ;
}

/**
 * @ingroup Tetris
 * @brief 동일한 Y 값인지 검사한다.
 * @param clsPart 검사 대상 정사각형 정보 저장 객체
 * @returns 동일한 Y 값이면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CTetrisBlockPart::IsSameY( CTetrisBlockPart & clsPart )
{
	float fY = GetDistance( GetY(), clsPart.GetY() );

	if( fY <= BOX_WIDTH / 8 ) return true;

	return false;
}

/**
 * @ingroup Tetris
 * @brief 충돌 여부를 검사한다.
 * @param clsPart				충돌 검사 대상 정사각형 정보 저장 객체
 * @param bCheckBottom	하단 충돌을 검사하면 true 를 입력하고 그렇지 않으면 false 를 입력한다.
 * @returns 하단과 충돌되었으면 CT_BOTTOM 을 리턴하고 좌/우로 충돌되었으면 CT_LEFT_RIGHT 를 리턴한다. 충돌되지 않았으면 CT_NULL 을 리턴한다.
 */
E_COLLISION_TYPE CTetrisBlockPart::CheckCollision( CTetrisBlockPart & clsPart, bool bCheckBottom )
{
	float fMyY = GetY();
	float fMyZ = GetZ();
	float fOtherY = clsPart.GetY();
	float fOtherZ = clsPart.GetZ();
	float fY = GetDistance( fMyY, fOtherY );
	float fZ = GetDistance( fMyZ, fOtherZ );

	if( bCheckBottom )
	{
		if( fZ <= BOX_WIDTH / 8 )
		{
			if( fY <= BOX_WIDTH * 7/8 )
			{
				return CT_BOTTOM;
			}
		}
	}

	if( fY <= BOX_WIDTH / 8 )
	{
		if( fZ <= BOX_WIDTH * 7/8 ) 
		{
			return CT_LEFT_RIGHT;
		}
	}

	return CT_NULL;
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록의 정사각형 리스트를 오름차순으로 정렬하는 함수
 * @param clsFirst	첫번째 정사각형 정보 저장 객체
 * @param clsSecond 두번째 정사각형 정보 저장 객체
 * @returns 두번째 정사각형 정보 저장 객체가 첫번째 정사각형 정보 저장 객체보다 뒤에 있으면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool TetrisBlockPartSort( const CTetrisBlockPart & clsFirst, const CTetrisBlockPart & clsSecond )
{
	float fFY = clsFirst.GetY();
	float fSY = clsSecond.GetY();
	float fY = GetDistance( fSY, fFY );

	if( fY <= BOX_WIDTH / 8 )
	{
		float fFZ = clsFirst.GetZ();
		float fSZ = clsSecond.GetZ();
		float fZ = GetDistance( fFZ, fSZ );

		if( fZ > BOX_WIDTH / 8 )
		{
			if( fSZ > fFZ ) return true;
		}
	}
	else
	{
		if( fSY > fFY ) return true;
	}

	return false;
}

/**
 * @ingroup Tetris
 * @brief 두 개의 float 의 거리 계산 함수
 * @param f1 첫번째 위치
 * @param f2 두번째 위치
 * @returns 두 개의 float 의 거리를 리턴한다.
 */
float GetDistance( float f1, float f2 )
{
	if( f1 >= f2 )
	{
		return f1 - f2;
	}

	return f2 - f1;
}
