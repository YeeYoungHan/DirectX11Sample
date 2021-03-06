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

#define BOX_COL_COUNT 10
#define BOX_ROW_COUNT	20

#include "TetrisBlockPart.h"

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 저장하는 클래스
 */
class CTetrisBlock
{
public:
	CTetrisBlock();

	void Create( E_BOX_COLOR eColor );
	void Clear( );

	void MoveRight( );
	void MoveLeft( );
	void MoveDown( float fDown );
	void Rotate( );

	void AddBlock( CTetrisBlock & clsBlock );
	bool CheckCompleteRow( );
	bool CheckGameOver( );
	E_COLLISION_TYPE CheckCollision( CTetrisBlock & clsBlock, bool bCheckBottom );
	TETRIS_BLOCK_PART_LIST * GetList();

private:
	bool AddPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor );

	TETRIS_BLOCK_PART_LIST m_clsList;
};
