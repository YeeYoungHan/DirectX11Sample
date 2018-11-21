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
#include <fstream>
#include <vector>
#include "check.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

CDirectX11::CDirectX11() : m_iQualityLevel(0)
{
}

CDirectX11::~CDirectX11()
{
}

/**
 * @ingroup LibDirectX11
 * @brief DirectX 사용을 위한 변수들을 생성한다.
 * @param hWnd 윈도우 핸들
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectX11::Create( HWND hWnd )
{
	D3D_FEATURE_LEVEL eFeatureLevel;

	CHECK_FAILED( D3D11CreateDevice( 0,	D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,	D3D11_SDK_VERSION, &m_pclsDevice, &eFeatureLevel, &m_pclsContext ) );
	if( eFeatureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		// DirectX 11 을 사용할 수 없다면 실패 처리한다.
		return false;
	}

	CHECK_FAILED( m_pclsDevice->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iQualityLevel ) );
	if( m_iQualityLevel <= 0 )
	{
		return false;
	}

	// 윈도우 크기를 가져온다.
	RECT clsRect;
	int iWidth, iHeight;

	if( GetClientRect( hWnd, &clsRect ) )
	{
		iWidth = clsRect.right - clsRect.left;
		iHeight = clsRect.bottom - clsRect.top;
	}

	// Swap Chain 을 생성한다.
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

	// RenderTargetView 를 생성한다.
	CComPtr<ID3D11Texture2D> pclsBackBuffer;

	CHECK_FAILED( m_pclsSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pclsBackBuffer) ) );
	CHECK_FAILED( m_pclsDevice->CreateRenderTargetView( pclsBackBuffer, 0, &m_pclsRenderTargetView ) );

	D3D11_TEXTURE2D_DESC sttT2D;
	
	sttT2D.Width     = iWidth;
	sttT2D.Height    = iHeight;
	sttT2D.MipLevels = 1;
	sttT2D.ArraySize = 1;
	sttT2D.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	sttT2D.SampleDesc.Count   = 4;
	sttT2D.SampleDesc.Quality = m_iQualityLevel-1;
	sttT2D.Usage          = D3D11_USAGE_DEFAULT;
	sttT2D.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	sttT2D.CPUAccessFlags = 0; 
	sttT2D.MiscFlags      = 0;

	CHECK_FAILED( m_pclsDevice->CreateTexture2D( &sttT2D, 0, &m_pclsDepthStencilBuffer ) );
	CHECK_FAILED( m_pclsDevice->CreateDepthStencilView( m_pclsDepthStencilBuffer, 0, &m_pclsDepthStencilView ) );

	m_pclsContext->OMSetRenderTargets( 1, &(m_pclsRenderTargetView.p), m_pclsDepthStencilView );
	//m_pclsContext->OMSetRenderTargets( 1, &(m_pclsRenderTargetView.p), NULL );

	m_sttScreenViewport.TopLeftX = 0;
	m_sttScreenViewport.TopLeftY = 0;
	m_sttScreenViewport.Width    = (float)iWidth;
	m_sttScreenViewport.Height   = (float)iHeight;
	m_sttScreenViewport.MinDepth = 0.0f;
	m_sttScreenViewport.MaxDepth = 1.0f;

	m_pclsContext->RSSetViewports( 1, &m_sttScreenViewport );

	CreateChild();

	return true;
}

/**
 * @ingroup LibDirectX11
 * @brief DirectX 로 화면에 그려준다.
 * @returns 성공하면 true 를 리턴하고 그렇지 않으면 false 를 리턴한다.
 */
bool CDirectX11::Draw()
{
	XMVECTORF32 sttWhite = {1.0f, 1.0f, 1.0f, 1.0f};

	m_pclsContext->ClearRenderTargetView( m_pclsRenderTargetView, (float*)&sttWhite );
	m_pclsContext->ClearDepthStencilView( m_pclsDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0 );
	m_pclsContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	if( DrawChild() == false ) return false;

	CHECK_FAILED( m_pclsSwapChain->Present( 0, 0 ) );

	return true;
}

/**
 * @ingroup LibDirectX11
 * @brief .fxo 파일에서 ID3DX11Effect 객체의 포인터를 생성한다.
 * @param pszFxoFile	.fx 파일을 컴파일한 .fxo 파일 full path
 * @param ppclsEffect [out] .fxo 파일로 생성된 ID3DX11Effect 객체의 포인터
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool CDirectX11::CreateEffect( const char * pszFxoFile, ID3DX11Effect ** ppclsEffect )
{
	std::ifstream clsIn( pszFxoFile, std::ios::binary );
	
	clsIn.seekg( 0, std::ios_base::end );
	int iSize = (int)clsIn.tellg();
	if( iSize == -1 ) CHECK_FAILED( NTE_NOT_FOUND );
	
	clsIn.seekg( 0, std::ios_base::beg );
	std::vector<char> arrData(iSize);

	clsIn.read( &arrData[0], iSize );
	clsIn.close();

	CHECK_FAILED( D3DX11CreateEffectFromMemory( &arrData[0], iSize, 0, m_pclsDevice, ppclsEffect ) );

	return true;
}
