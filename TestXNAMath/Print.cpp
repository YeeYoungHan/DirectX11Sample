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

#include "TestXNAMath.h"

/** XMVECTOR 를 stdout 에 출력한다. */
void PrintVector( XMVECTOR & sttVec )
{
	printf( "[ %f, %f, %f, %f ]\n", sttVec.m128_f32[0], sttVec.m128_f32[1], sttVec.m128_f32[2], sttVec.m128_f32[3] );
}

/** XMFLOAT4 를 stdout 에 출력한다. */
void PrintFloat4( XMFLOAT4 & sttFloat4 )
{
	printf( "[ %f, %f, %f, %f ]\n", sttFloat4.x, sttFloat4.y, sttFloat4.z, sttFloat4.w );
}

/** XMMATRIX 를 stdout 에 출력한다. */
void PrintMatrix( XMMATRIX & sttMat )
{
	printf( "+----------------------------------------+\n" );
	printf( "| %.6f, %.6f, %.6f, %.6f |\n", sttMat._11, sttMat._12, sttMat._13, sttMat._14 );
	printf( "| %.6f, %.6f, %.6f, %.6f |\n", sttMat._21, sttMat._22, sttMat._23, sttMat._24 );
	printf( "| %.6f, %.6f, %.6f, %.6f |\n", sttMat._31, sttMat._32, sttMat._33, sttMat._34 );
	printf( "| %.6f, %.6f, %.6f, %.6f |\n", sttMat._41, sttMat._42, sttMat._43, sttMat._44 );
	printf( "+----------------------------------------+\n" );
}
