// CommonCheck.h: interface for the CCommonCheck class.
// ����ͨ��У���ʵ��
// �����ݷǿա����ֵ�У��
// �����ˣ��˷�
// ����ʱ�䣺2007-1-14 8:41
//////////////////////////////////////////////////////////////////////
#pragma once
 
namespace CommonCheck  
{
	// ��У��
	BOOL IsEmpty( CString & source );
	// ��У�飬Ϊ�ո�����ʾ
	BOOL IsEmpty( CString & source, CString message );
	// ��У�飬Ϊ�ո�����ʾ�����������Ƶ���Ӧ�Ŀؼ�
	BOOL IsEmpty( CString & source, CString message, CWnd & ctrl );

	// ���ּ���
	// ����У��
	BOOL IsInt( CString & source );
	// ����У�飬��������������ʾ
	BOOL IsInt( CString & source, CString message );
	// ����У�飬��������������ʾ�����������Ƶ���Ӧ�Ŀؼ�
	BOOL IsInt( CString & source, CString message, CWnd & ctrl );

	// ����У�飨������������С����
	BOOL IsNum( CString & source );
	// ����У�飬�������ָ�����ʾ
	BOOL IsNum( CString & source, CString message );
	// ����У�飬�������ָ�����ʾ�����������Ƶ���Ӧ�Ŀؼ�
	BOOL IsNum( CString & source, CString message, CWnd & ctrl );
};