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

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 생성한다.
 * @param eColor 테트리스 블록 색상
 */
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

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 초기화시킨다.
 */
void CTetrisBlock::Clear( )
{
	m_clsList.clear();
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 오른쪽으로 이동시킨다.
 */
void CTetrisBlock::MoveRight( )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( 0, BOX_WIDTH );
	}
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 왼쪽으로 이동시킨다.
 */
void CTetrisBlock::MoveLeft( )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( 0, -BOX_WIDTH );
	}
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 아래로 이동시킨다.
 * @param fDown 아래로 이동시킬 거리
 */
void CTetrisBlock::MoveDown( float fDown )
{
	TETRIS_BLOCK_PART_LIST::iterator itPL;

	for( itPL = m_clsList.begin(); itPL != m_clsList.end(); ++itPL )
	{
		itPL->Move( fDown, 0 );
	}
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 추가한다.
 * @param clsBlock 추가할 테트리스 블록
 */
void CTetrisBlock::AddBlock( CTetrisBlock & clsBlock )
{
	TETRIS_BLOCK_PART_LIST::iterator itBL;

	for( itBL = clsBlock.m_clsList.begin(); itBL != clsBlock.m_clsList.end(); ++itBL )
	{
		m_clsList.push_back( *itBL );
	}
}

/**
 * @ingroup Tetris
 * @brief 1 row 가 완성되었다면 완성된 row 를 삭제하고 그 위의 row 들을 1칸씩 내린다.
 * @returns false 를 리턴한다.
 */
bool CTetrisBlock::CheckCompleteRow( )
{
	m_clsList.sort( TetrisBlockPartSort );

	TETRIS_BLOCK_PART_LIST::iterator itPL, itRow, itTemp;
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
		}
		else
		{
			if( iColCount == BOX_COL_COUNT )
			{
				// 모두 완성된 row 를 삭제한다.
				m_clsList.erase( itRow, itPL );

				// 모두 완성된 row 위에 존재하는 블록은 1칸씩 내린다.
				for( itTemp = itPL; itTemp != m_clsList.end(); ++itTemp )
				{
					itTemp->Move( -BOX_WIDTH, 0.0f );
				}
			}

			itRow = itPL;
			iColCount = 1;
		}
	}

	return false;
}

/**
 * @ingroup Tetris
 * @brief 게임이 종료되었는지 검사한다.
 * @returns 게임이 종료되었으면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CTetrisBlock::CheckGameOver( )
{
	TETRIS_BLOCK_PART_LIST::reverse_iterator itPL, itRow;
	CTetrisBlockPart clsPart( BOX_WIDTH * BOX_ROW_COUNT / 2, 0.0f, BC_RED );

	for( itPL = m_clsList.rbegin(); itPL != m_clsList.rend(); ++itPL )
	{
		if( itPL->IsSameY( clsPart ) )
		{
			return true;
		}

		if( itPL == m_clsList.rbegin() )
		{
			itRow = itPL;
		}
		else if( itRow->IsSameY( *itPL ) )
		{
			break;
		}
	}

	return false;
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록을 회전시킨다.
 */
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

/**
 * @ingroup Tetris
 * @brief 테트리스 블록과 충돌되었는지 검사한다.
 * @param clsBlock			충돌 검사 대상 테트리스 블록
 * @param bCheckBottom	하단 충돌 검사하려면 true 를 입력하고 그렇지 않으면 false 를 입력한다.
 * @returns 하단과 충돌되었으면 CT_BOTTOM 을 리턴하고 좌/우로 충돌되었으면 CT_LEFT_RIGHT 를 리턴한다. 충돌되지 않았으면 CT_NULL 을 리턴한다.
 */
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

/**
 * @ingroup Tetris
 * @brief 테트리스 블록에 포함된 정사각형 리스트의 포인터를 리턴한다.
 * @returns 테트리스 블록에 포함된 정사각형 리스트의 포인터를 리턴한다.
 */
TETRIS_BLOCK_PART_LIST * CTetrisBlock::GetList()
{
	return &m_clsList;
}

/**
 * @ingroup Tetris
 * @brief 테트리스 블록에 정사각형 1개를 추가한다.
 * @param fLocalY		Y 위치
 * @param fLocalZ		Z 위치
 * @param eColor		텍스처 번호
 * @returns true 를 리턴한다.
 */
bool CTetrisBlock::AddPart( float fLocalY, float fLocalZ, E_BOX_COLOR eColor )
{
	CTetrisBlockPart clsPart( fLocalY, fLocalZ, eColor );
	
	m_clsList.push_back( clsPart );

	return true;
}
