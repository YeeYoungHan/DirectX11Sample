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
		// 좌/우 테두리
		for( int i = 0; i < ( BOX_ROW_COUNT + 2 ); ++i )
		{
			AddPart( -BOX_WIDTH * BOX_ROW_COUNT / 2 + i * BOX_WIDTH, -BOX_WIDTH * ( BOX_COL_COUNT / 2 + 1 ), eColor );
			AddPart( -BOX_WIDTH * BOX_ROW_COUNT / 2 + i * BOX_WIDTH, BOX_WIDTH * BOX_COL_COUNT / 2, eColor );
		}
		break;
	case BC_BLACK_TOP:
		// 상단 테두리
		for( int i = 0; i < BOX_COL_COUNT; ++i )
		{
			AddPart( BOX_WIDTH * ( BOX_ROW_COUNT / 2 + 1 ), -BOX_WIDTH * BOX_COL_COUNT / 2 + i * BOX_WIDTH, eColor );
		}
		break;
	case BC_BLACK_BOTTOM:
		// 하단 테두리
		for( int i = 0; i < BOX_COL_COUNT; ++i )
		{
			AddPart( -BOX_WIDTH * BOX_ROW_COUNT / 2, -BOX_WIDTH * BOX_COL_COUNT / 2 + i * BOX_WIDTH, eColor );
		}
		break;
	}
}

void CTetrisBlock::Clear( )
{
	m_clsList.clear();
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

void CTetrisBlock::AddBlock( CTetrisBlock & clsBlock )
{
	TETRIS_BLOCK_PART_LIST::iterator itBL;

	for( itBL = clsBlock.m_clsList.begin(); itBL != clsBlock.m_clsList.end(); ++itBL )
	{
		m_clsList.push_back( *itBL );
	}
}

bool CTetrisBlock::CheckCompleteRow( )
{
	m_clsList.sort( TetrisBlockPartSort );

	TETRIS_BLOCK_PART_LIST::iterator itPL, itRow;
	int iColCount = 0;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		if( itPL == m_clsList.begin() )
		{
			itRow = itPL;
			iColCount = 1;
		}
		else if( itRow->IsSameY( *itPL ) )
		{
			++iColCount;
			if( iColCount == BOX_COL_COUNT )
			{
				
			}
		}
		else
		{
			itRow = itPL;
			iColCount = 1;
		}
	}

	return false;
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

E_COLLISION_TYPE CTetrisBlock::CheckCollision( CTetrisBlock & clsBlock, bool bCheckBottom )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL, itBL;
	E_COLLISION_TYPE eType = CT_NULL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		for( itBL = clsBlock.m_clsList.begin(); itBL != clsBlock.m_clsList.end(); ++itBL )
		{
			eType = itPL->CheckCollision( *itBL, bCheckBottom );
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
