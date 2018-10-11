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

#ifndef _DIRECT_X11_H_
#define _DIRECT_X11_H_

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <string>
#include <atlbase.h>
#include <d3dx11.h>
#include <xnamath.h>

class CDirectX11
{
public:
	CDirectX11();
	virtual ~CDirectX11();

	bool Create( HWND hWnd );
	bool Draw();

	virtual bool CreateChild() = 0;
	virtual bool DrawChild() = 0;

	const TCHAR * GetErrString();

protected:
	CComPtr<ID3D11Device> m_pclsDevice;
	CComPtr<ID3D11DeviceContext> m_pclsContext;
	CComPtr<IDXGISwapChain> m_pclsSwapChain;

	UINT      m_iQualityLevel;

	// 에러 정보
	HRESULT m_iErrCode;
	std::wstring m_strErrFunc;
	std::wstring m_strErrFile;
	int m_iErrLine;
	TCHAR m_szErrMsg[1024];
};

#define CHECK_FAILED(x)    \
{                          \
	HRESULT hrt = (x);       \
	if( FAILED(hrt) )        \
	{                        \
		WCHAR szBuf[512];      \
		MultiByteToWideChar( CP_ACP, 0, __FILE__, -1, szBuf, 512 ); \
		m_iErrCode = hrt;      \
		m_strErrFunc = L#x;    \
		m_strErrFile = szBuf;  \
		m_iErrLine = __LINE__; \
		return false;          \
	}                        \
}

#endif
