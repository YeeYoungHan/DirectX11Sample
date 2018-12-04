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

#define BOX_WIDTH	0.16f

#include <list>

enum E_BOX_COLOR
{
	BC_BLUE = 0,
	BC_GREEN,
	BC_ORANGE,
	BC_RED,
	BC_SKYBLUE,
	BC_VILOET,
	BC_YELLOW,
	BC_BLACK,
	BC_BLACK_TOP
};

enum E_COLLISION_TYPE
{
	CT_NULL,
	CT_LEFT_RIGHT,
	CT_BOTTOM
};

class CTetrisBlockPart
{
public:
	CTetrisBlockPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor );

	void Move( float fY, float fZ );
	void Rotate();
	float GetY();
	float GetZ();
	E_COLLISION_TYPE CheckCollision( CTetrisBlockPart & clsPart );

	E_BOX_COLOR m_eColor;

private:
	float	m_fLocalY;
	float	m_fLocalZ;
	float m_fWorldY;
	float m_fWorldZ;
};

typedef std::list< CTetrisBlockPart > TETRIS_BLOCK_PART_LIST;
