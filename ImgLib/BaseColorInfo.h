//////////////////////////////////////////////////////////////////////////
// BaseColorInfo.h: interface for the CBaseColorInfo class.
// ��ɫ��ɫ��Ϣ
// ������: �˷�
// ����ʱ��: 2008-03-27
//////////////////////////////////////////////////////////////////////
#pragma once

class CBaseColorInfo  
{
public:
	CBaseColorInfo( int red = 0, int green = 0, int blue = 0 );

public:
	// ��
	int GetRed() const;
	void SetRed( int red );
	// ��
	int GetGreen() const;
	void SetGreen( int green );
	// ��
	int GetBlue() const;
	void SetBlue( int blue );

public:
	// ���������
	// ��ֵ�����
	CBaseColorInfo & operator =( CBaseColorInfo & pixel );
	// �ж��Ƿ���ͬ�����
	bool operator == ( CBaseColorInfo & pixel );

private:
	// ��
	int _red;
	// ��
	int _green;
	// ��
	int _blue;

};