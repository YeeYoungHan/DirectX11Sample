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

void PrintVector( XMVECTOR & sttVec )
{
	printf( "[ %f, %f, %f, %f ]\n", sttVec.m128_f32[0], sttVec.m128_f32[1], sttVec.m128_f32[2], sttVec.m128_f32[3] );
}

void PrintFloat4( XMFLOAT4 & sttFloat4 )
{
	printf( "[ %f, %f, %f, %f ]\n", sttFloat4.x, sttFloat4.y, sttFloat4.z, sttFloat4.w );
}

void TestVector()
{
	XMVECTOR sttVec;

	// XMFLOAT2 변수에 저장된 내용을 XMVECTOR 에 저장한다.
	XMFLOAT2 sttFloat2( 1.0, 2.0 );

	sttVec = XMLoadFloat2( &sttFloat2 );
	PrintVector( sttVec );
	// [ 1.000000, 2.000000, 0.000000, 0.000000 ]

	// XMVECTOR 의 z, w 에 값을 저장한다.
	sttVec = XMVectorSetZ( sttVec, 3.0 );
	sttVec = XMVectorSetW( sttVec, 4.0 );

	// XMVECTOR 에 저장된 내용을 XMFLOAT4 에 저장한다.
	XMFLOAT4 sttFloat4;

	XMStoreFloat4( &sttFloat4, sttVec );
	PrintFloat4( sttFloat4 );
	// [ 1.000000, 2.000000, 3.000000, 4.000000 ]

	// XMVECTOR 의 x, y, z, w 를 출력한다.
	printf( "[ %f, %f, %f, %f ]\n", XMVectorGetX( sttVec ), XMVectorGetY( sttVec ), XMVectorGetZ( sttVec ), XMVectorGetW( sttVec ) );
	// [ 1.000000, 2.000000, 3.000000, 4.000000 ]

	FLOAT fX;

	XMVectorGetXPtr( &fX, sttVec );
	printf( "x = %f\n", fX );
	// x = 1.000000
}
