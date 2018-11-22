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

#include "Effect.h"
#include <string>
#include <vector>
#include <fstream>
#include "check.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

bool CEffect::Create( ID3D11Device * pclsDevice, ID3D11DeviceContext * pclsContext, const char * pszFileName )
{
	m_pclsDevice = pclsDevice;
	m_pclsContext = pclsContext;

	// 컴파일된 fx 파일을 로그한다.
	if( CreateEffect( pszFileName, &m_pclsEffect ) == false ) return false;

	// fx 파일에 정의된 변수와 연결한다.
	m_pclsEffectTech = m_pclsEffect->GetTechniqueByName("ColorTech");
	m_pclsWorldViewProj = m_pclsEffect->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_pclsWorld = m_pclsEffect->GetVariableByName("gWorld")->AsMatrix();
	m_pclsWorldInvTranspose = m_pclsEffect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_pclsEyePosW = m_pclsEffect->GetVariableByName("gEyePosW")->AsVector();
	m_pclsDirectionalLight = m_pclsEffect->GetVariableByName("gDirLight");
	m_pclsMaterial = m_pclsEffect->GetVariableByName("gMaterial");
	m_pclsShaderResVar = m_pclsEffect->GetVariableByName("gShaderResVar")->AsShaderResource();
	m_pclsUseTexture = m_pclsEffect->GetVariableByName("gUseTexture")->AsScalar();

	return true;
}

bool CEffect::CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC * parrVertexDesc, int iVertexDescCount, ID3D11InputLayout ** pclsInputLayout )
{
	if( m_pclsDevice == NULL || m_pclsEffectTech == NULL ) return false;

	D3DX11_PASS_DESC sttPassDesc;

	m_pclsEffectTech->GetPassByIndex(0)->GetDesc( &sttPassDesc );
	CHECK_FAILED( m_pclsDevice->CreateInputLayout( parrVertexDesc, iVertexDescCount, sttPassDesc.pIAInputSignature, sttPassDesc.IAInputSignatureSize, pclsInputLayout ) );

	return true;
}

bool CEffect::SetWorld( XMFLOAT4X4 * psttWorld, XMMATRIX * psttWorldViewProj, XMMATRIX * psttWorldInvTranspose )
{
	if( m_pclsWorld == NULL || m_pclsWorldViewProj == NULL || m_pclsWorldInvTranspose == NULL ) return false;

	m_pclsWorld->SetMatrix( (float*)psttWorld );
	m_pclsWorldViewProj->SetMatrix( (float*)psttWorldViewProj );
	m_pclsWorldInvTranspose->SetMatrix( (float*)psttWorldInvTranspose );

	return true;
}

bool CEffect::SetShaderResourceView( ID3D11ShaderResourceView * pclsShaderResView )
{
	if( m_pclsShaderResVar == NULL || m_pclsUseTexture == NULL ) return false;

	if( pclsShaderResView )
	{
		m_pclsShaderResVar->SetResource( pclsShaderResView );
		m_pclsUseTexture->SetBool(TRUE);
	}
	else
	{
		m_pclsUseTexture->SetBool(FALSE);
	}

	return true;
}

bool CEffect::SetMaterial( CMaterial * pclsMaterial )
{
	if( m_pclsMaterial == NULL ) return false;

	m_pclsMaterial->SetRawValue( pclsMaterial, 0, sizeof(CMaterial) );

	return true;
}

bool CEffect::SetDirectionalLight( XMFLOAT4 & f4Ambient, XMFLOAT4 & f4Diffuse, XMFLOAT4 & f4Specular, XMFLOAT3 & f3Direction )
{
	if( m_pclsDirectionalLight == NULL ) return false;

	CDirectionalLight clsLight;

	clsLight.m_f4Ambient = f4Ambient;
	clsLight.m_f4Diffuse = f4Diffuse;
	clsLight.m_f4Specular = f4Specular;
	clsLight.m_f3Direction = f3Direction;

	m_pclsDirectionalLight->SetRawValue( &clsLight, 0, sizeof(clsLight) );

	return true;
}

bool CEffect::SetEyePos( XMFLOAT3 * psttEyePos )
{
	if( m_pclsEyePosW == NULL ) return false;

	m_pclsEyePosW->SetRawValue( psttEyePos, 0, sizeof(XMFLOAT3) );

	return true;
}

bool CEffect::Apply( int iPassIndex )
{
	if( m_pclsEffectTech == NULL || m_pclsContext == NULL ) return false;

	m_pclsEffectTech->GetPassByIndex(iPassIndex)->Apply( 0, m_pclsContext );

	return true;
}

int CEffect::GetPassCount()
{
	if( m_pclsEffectTech == NULL ) return -1;

	D3DX11_TECHNIQUE_DESC sttTechDesc;
	m_pclsEffectTech->GetDesc( &sttTechDesc );

	return sttTechDesc.Passes;
}

/**
 * @ingroup LibDirectX11
 * @brief .fxo 파일에서 ID3DX11Effect 객체의 포인터를 생성한다.
 * @param pszFxoFile	.fx 파일을 컴파일한 .fxo 파일 full path
 * @param ppclsEffect [out] .fxo 파일로 생성된 ID3DX11Effect 객체의 포인터
 * @returns 성공하면 true 를 리턴하고 실패하면 false 를 리턴한다.
 */
bool CEffect::CreateEffect( const char * pszFxoFile, ID3DX11Effect ** ppclsEffect )
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
