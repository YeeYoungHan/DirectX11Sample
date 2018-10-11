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

#include "DirectX11.h"
#include <comdef.h>

CDirectX11::CDirectX11() : m_iQualityLevel(0)
{
}

CDirectX11::~CDirectX11()
{
}

bool CDirectX11::Create( HWND hWnd )
{
	D3D_FEATURE_LEVEL eFeatureLevel;

	CHECK_FAILED( D3D11CreateDevice( 0,	D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,	D3D11_SDK_VERSION, &m_pclsDevice, &eFeatureLevel, &m_pclsContext ) );
	if( eFeatureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		return false;
	}

	CHECK_FAILED( m_pclsDevice->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQualityLevel ) );
	if( m_iQualityLevel <= 0 )
	{
		return false;
	}

	RECT clsRect;
	int iWidth, iHeight;

	if( GetClientRect( hWnd, &clsRect ) )
	{
		iWidth = clsRect.right - clsRect.left;
		iHeight = clsRect.bottom - clsRect.top;
	}

	DXGI_SWAP_CHAIN_DESC sttSCD;
	
	sttSCD.BufferDesc.Width  = iWidth;
	sttSCD.BufferDesc.Height = iHeight;
	sttSCD.BufferDesc.RefreshRate.Numerator = 60;
	sttSCD.BufferDesc.RefreshRate.Denominator = 1;
	sttSCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sttSCD.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sttSCD.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sttSCD.SampleDesc.Count   = 4;
	sttSCD.SampleDesc.Quality = m_iQualityLevel-1;

	sttSCD.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sttSCD.BufferCount  = 1;
	sttSCD.OutputWindow = hWnd;
	sttSCD.Windowed     = true;
	sttSCD.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sttSCD.Flags        = 0;

	CComPtr<IDXGIDevice> pclsDxDevice;
	CComPtr<IDXGIAdapter> pclsDxAdapter;
	CComPtr<IDXGIFactory> pclsDxFactory;

	CHECK_FAILED( m_pclsDevice->QueryInterface( __uuidof(IDXGIDevice), (void**)&pclsDxDevice ) );
	CHECK_FAILED( pclsDxDevice->GetParent( __uuidof(IDXGIAdapter), (void**)&pclsDxAdapter ) );
	CHECK_FAILED( pclsDxAdapter->GetParent( __uuidof(IDXGIFactory), (void**)&pclsDxFactory ) );
	CHECK_FAILED( pclsDxFactory->CreateSwapChain( m_pclsDevice, &sttSCD, &m_pclsSwapChain ) );

	return true;
}

bool CDirectX11::Draw()
{

	return true;
}

/**
 * @ingroup LibDirectX11
 * @brief DirectX11 함수 사용시 발생한 오류 정보 문자열을 가져온다.
 * @returns DirectX11 함수 사용시 발생한 오류 정보 문자열을 리턴한다.
 */
const TCHAR * CDirectX11::GetErrString()
{
	_com_error clsError( m_iErrCode );

	_sntprintf( m_szErrMsg, sizeof(m_szErrMsg)/sizeof(TCHAR), _T("hr=%d;\r\nmsg=%s;\r\nfile=%s;\r\nline=%d\r\nfunc=%s")
		, m_iErrCode, clsError.ErrorMessage(), m_strErrFile.c_str(), m_iErrLine, m_strErrFunc.c_str() );

	return m_szErrMsg;
}
