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
#include "TestDXUT.h"
#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTmisc.h"
#include "SDKmisc.h"
#include "trace.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_BTN_1	1
#define ID_CHK_1	3
#define ID_SLD_1	5

CDXUTDialogResourceManager gclsDRM;
CDXUTDialog gclsDlg;

bool CALLBACK Device9AcceptableCallBack( D3DCAPS9 * pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void * pUserContext )
{
	return false;
}

bool CALLBACK Device11AcceptableCallBack( const CD3D11EnumAdapterInfo * AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo * DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void * pUserContext )
{
	return true;
}

HRESULT CALLBACK DeviceCreatedCallBack( ID3D11Device * pd3dDevice, const DXGI_SURFACE_DESC * pBackBufferSurfaceDesc, void * pUserContext )
{
	HRESULT hr;

	V_RETURN( DXUTSetMediaSearchPath( _T("..\\LIbDXUT11\\Media\\") ) );
	V_RETURN( gclsDRM.OnD3D11CreateDevice( DXUTGetD3D11Device(), DXUTGetD3D11DeviceContext() ) );

	return S_OK;
}

void CALLBACK DeviceDestroyedCallBack( void * pUserContext )
{
	gclsDRM.OnD3D11DestroyDevice();
}

void CALLBACK FrameRenderCallBack( ID3D11Device * pd3dDevice, ID3D11DeviceContext * pd3dImmediateContext, double fTime, float fElapsedTime, void * pUserContext )
{
  float ClearColor[4] = { 0.0f, 0.0, 0.0, 0.0f };
  ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
  pd3dImmediateContext->ClearRenderTargetView( pRTV, ClearColor );

  ID3D11DepthStencilView * pDSV = DXUTGetD3D11DepthStencilView();
  pd3dImmediateContext->ClearDepthStencilView( pDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );

	gclsDlg.OnRender( fElapsedTime );
}

HRESULT CALLBACK SwapChainResizedCallBack( ID3D11Device * pd3dDevice, IDXGISwapChain * pSwapChain, const DXGI_SURFACE_DESC * pBackBufferSurfaceDesc, void * pUserContext )
{
	HRESULT hr;

	V_RETURN( gclsDRM.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );

	gclsDlg.SetLocation( 0, 0 );
	gclsDlg.SetSize( 700, 300 );

	return S_OK;
}

void CALLBACK SwapChainReleasingCallBack( void* pUserContext )
{
	gclsDRM.OnD3D11ReleasingSwapChain();
}

LRESULT CALLBACK MsgProcCallBack( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool * pbNoFurtherProcessing, void * pUserContext )
{
	*pbNoFurtherProcessing = gclsDRM.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing ) return 0;

	*pbNoFurtherProcessing = gclsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing ) return 0;

	return 0;
}

void CALLBACK DlgCallBack( UINT nEvent, int nControlID, CDXUTControl * pControl, void * pUserContext )
{
	switch( nControlID )
	{
	case ID_BTN_1:
		MessageBox( NULL, _T("Button #1 is clicked"), _T("Debug"), MB_OK );
		break;
	case ID_CHK_1:
		if( ((CDXUTCheckBox*)pControl)->GetChecked() )
		{
			MessageBox( NULL, _T("Check #1 is checked"), _T("Debug"), MB_OK );
		}
		else
		{
			MessageBox( NULL, _T("Check #1 is not checked"), _T("Debug"), MB_OK );
		}
		break;
	case ID_SLD_1:
		{
			int iCurVal = ((CDXUTSlider*)pControl)->GetValue();

			TRACE( "Slider #1 pos(%d)\r\n", iCurVal );
		}
		break;
	}
}

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	DXUTSetCallbackD3D9DeviceAcceptable( Device9AcceptableCallBack );
	DXUTSetCallbackD3D11DeviceAcceptable( Device11AcceptableCallBack );
	DXUTSetCallbackD3D11DeviceCreated( DeviceCreatedCallBack );
	DXUTSetCallbackD3D11DeviceDestroyed( DeviceDestroyedCallBack );
	DXUTSetCallbackD3D11FrameRender( FrameRenderCallBack );
	DXUTSetCallbackD3D11SwapChainResized( SwapChainResizedCallBack );
	DXUTSetCallbackD3D11SwapChainReleasing( SwapChainReleasingCallBack );
	DXUTSetCallbackMsgProc( MsgProcCallBack );

	gclsDlg.Init( &gclsDRM );
	gclsDlg.SetCallback( DlgCallBack );

	int iY = 10;

	gclsDlg.AddStatic( 0, _T("Static"), 10, iY, 160, 22 );
	iY += 30;

	gclsDlg.AddButton( ID_BTN_1, _T("Button #1"), 10, iY, 160, 22 );
	iY += 30;

	gclsDlg.AddCheckBox( ID_CHK_1, _T("Check #1"), 10, iY, 160, 22 );
	iY += 30;

	gclsDlg.AddSlider( ID_SLD_1, 10, iY, 160, 22 );
	iY += 30;

	DXUTInit( true, true, NULL );
  DXUTSetCursorSettings( true, true );
  DXUTCreateWindow( _T("TestDXUT") );
	DXUTCreateDevice( D3D_FEATURE_LEVEL_11_0, true, 700, 300 );

	DXUTMainLoop();

	return DXUTGetExitCode();
}
