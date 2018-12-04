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

CTetrisBlockPart::CTetrisBlockPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor ) : m_fLocalY(fLocalY), m_fLocalZ(fLocalZ), m_fWorldY(0.0f), m_fWorldZ(0.0f), m_eColor(eColor)
{
}

void CTetrisBlockPart::Move( float fY, float fZ )
{
	m_fWorldY += fY;
	m_fWorldZ += fZ;
}

void CTetrisBlockPart::Rotate()
{
	float fTemp = m_fLocalY;
	m_fLocalY = m_fLocalZ;
	m_fLocalZ = fTemp;

	m_fLocalZ *= -1;
}

float CTetrisBlockPart::GetY()
{
	return m_fWorldY + m_fLocalY;
}

float CTetrisBlockPart::GetZ()
{
	return m_fWorldZ + m_fLocalZ;
}

E_COLLISION_TYPE CTetrisBlockPart::CheckCollision( CTetrisBlockPart & clsPart )
{
	float fMyY = GetY();
	float fMyZ = GetZ();
	float fOtherY = clsPart.GetY();
	float fOtherZ = clsPart.GetZ();
	float fY, fZ;

	if( fMyY >= fOtherY )
	{
		fY = fMyY - fOtherY;
	}
	else
	{
		fY = fOtherY - fMyY;
	}

	if( fMyZ >= fOtherZ )
	{
		fZ = fMyZ - fOtherZ;
	}
	else
	{
		fZ = fOtherZ - fMyZ;
	}

	if( fZ <= BOX_WIDTH / 8 )
	{
		if( fY <= BOX_WIDTH * 7/8 ) return CT_BOTTOM;
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
