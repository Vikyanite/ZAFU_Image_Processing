//////////////////////////////////////////////////////////////////////////
// BaseColorInfo.h: interface for the CBaseColorInfo class.
// 颜色基色信息
// 创建人: 邓飞
// 创建时间: 2008-03-27
//////////////////////////////////////////////////////////////////////
#pragma once

class CBaseColorInfo  
{
public:
	CBaseColorInfo( int red = 0, int green = 0, int blue = 0 );

public:
	// 红
	int GetRed() const;
	void SetRed( int red );
	// 绿
	int GetGreen() const;
	void SetGreen( int green );
	// 蓝
	int GetBlue() const;
	void SetBlue( int blue );

public:
	// 运算符重载
	// 赋值运算符
	CBaseColorInfo & operator =( CBaseColorInfo & pixel );
	// 判断是否相同运算符
	bool operator == ( CBaseColorInfo & pixel );

private:
	// 红
	int _red;
	// 绿
	int _green;
	// 蓝
	int _blue;

};