// BaseColorInfo.cpp: implementation of the CBaseColorInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseColorInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseColorInfo::CBaseColorInfo( int red , int green , int blue  )
{
	SetRed( red );
	SetGreen( green );
	SetBlue( blue );
}

/************************************************************************/
/*                            ��������                                  */
/************************************************************************/
// ��
int CBaseColorInfo::GetRed() const{
	return _red;
}
void CBaseColorInfo::SetRed( int red ){

	if( red > 255 ){
		_red = 255;
	}
	else if( red < 0 ){
		_red = 0;
	}
	else{
		_red = red;
	}

}

// ��
int CBaseColorInfo::GetGreen() const{
	return _green;
}
void CBaseColorInfo::SetGreen( int green ){
	
	if( green > 255 ){
		_green = 255;
	}
	else if( green < 0 ){
		_green = 0;
	}
	else{
		_green = green;
	}

}

// ��
int CBaseColorInfo::GetBlue() const{
	return _blue;
}
void CBaseColorInfo::SetBlue( int blue ){
	
	if( blue > 255 ){
		_blue = 255;
	}
	else if( blue < 0 ){
		_blue = 0;
	}
	else{
		_blue = blue;
	}

}

/************************************************************************/
/*                          ���������                                  */
/************************************************************************/
// ��ֵ�����
CBaseColorInfo & CBaseColorInfo::operator =( CBaseColorInfo & pixel ){

	SetRed( pixel.GetRed() );
	SetGreen( pixel.GetGreen() );
	SetBlue( pixel.GetBlue() );

	return *this;

}

// �ж��Ƿ���ͬ�����
// �졢�̡���������������ͬ������������ͬ������ͬ
bool CBaseColorInfo::operator == ( CBaseColorInfo & pixel ){

	return ( _red == pixel.GetRed() 
		&& _green == pixel.GetGreen() 
		&& pixel.GetRed() );

}
