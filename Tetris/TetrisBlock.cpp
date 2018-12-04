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

CTetrisBlock::CTetrisBlock()
{
}

void CTetrisBlock::Create( E_BOX_COLOR eColor )
{
	m_clsList.clear();

	switch( eColor )
	{
	case BC_BLUE:
		AddPart( BOX_WIDTH, -BOX_WIDTH, eColor );
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		AddPart( 0, BOX_WIDTH, eColor );
		break;
	case BC_GREEN:
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		AddPart( BOX_WIDTH, 0, eColor );
		AddPart( BOX_WIDTH, BOX_WIDTH, eColor );
		break;
	case BC_ORANGE:
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		AddPart( 0, BOX_WIDTH, eColor );
		AddPart( BOX_WIDTH, BOX_WIDTH, eColor );
		break;
	case BC_RED:
		AddPart( BOX_WIDTH, -BOX_WIDTH, eColor );
		AddPart( BOX_WIDTH, 0, eColor );
		AddPart( 0, 0, eColor );
		AddPart( 0, BOX_WIDTH, eColor );
		break;
	case BC_SKYBLUE:
		AddPart( 0, -BOX_WIDTH * 2, eColor );
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		AddPart( 0, BOX_WIDTH, eColor );
		break;
	case BC_VILOET:
		AddPart( BOX_WIDTH, 0, eColor );
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		AddPart( 0, BOX_WIDTH, eColor );
		break;
	case BC_YELLOW:
		AddPart( BOX_WIDTH, -BOX_WIDTH, eColor );
		AddPart( BOX_WIDTH, 0, eColor );
		AddPart( 0, -BOX_WIDTH, eColor );
		AddPart( 0, 0, eColor );
		break;
	case BC_BLACK:
		// 하단 테두리
		for( int i = 0; i < 12; ++i )
		{
			AddPart( -BOX_WIDTH * 10, -BOX_WIDTH * 6 + i * BOX_WIDTH, eColor );
		}

		// 좌/우 테두리
		for( int i = 0; i < 20; ++i )
		{
			AddPart( -BOX_WIDTH * 9 + i * BOX_WIDTH, -BOX_WIDTH * 6, eColor );
			AddPart( -BOX_WIDTH * 9 + i * BOX_WIDTH, BOX_WIDTH * 5, eColor );
		}
		break;
	case BC_BLACK_TOP:
		// 상단 테두리
		for( int i = 0; i < 12; ++i )
		{
			AddPart( BOX_WIDTH * 11, -BOX_WIDTH * 6 + i * BOX_WIDTH, eColor );
		}
		break;
	}
}

void CTetrisBlock::MoveRight( )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( 0, BOX_WIDTH );
	}
}

void CTetrisBlock::MoveLeft( )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( 0, -BOX_WIDTH );
	}
}

void CTetrisBlock::MoveDown( float fDown )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( fDown, 0 );
	}
}

void CTetrisBlock::Rotate( )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		// 정사각형은 회전할 필요가 없다.
		if( itPL->m_eColor == BC_YELLOW ) return;

		itPL->Rotate();
	}
}

E_COLLISION_TYPE CTetrisBlock::CheckCollision( CTetrisBlock & clsBlock )
{
	TETRIS_BLOCK_PART_LIST * pclsList = clsBlock.GetList();
	TETRIS_BLOCK_PART_LIST::iterator itPL, itIPL;
	E_COLLISION_TYPE eType = CT_NULL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		for( itIPL = pclsList->begin(); itIPL != pclsList->end(); ++itIPL )
		{
			eType = itPL->CheckCollision( *itIPL );
			if( eType != CT_NULL ) break;
		}

		if( eType != CT_NULL ) break;
	}

	return eType;
}

TETRIS_BLOCK_PART_LIST * CTetrisBlock::GetList()
{
	return &m_clsList;
}

bool CTetrisBlock::AddPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor )
{
	CTetrisBlockPart clsPart( fLocalY, fLocalZ, eColor );
	
	m_clsList.push_back( clsPart );

	return true;
}
