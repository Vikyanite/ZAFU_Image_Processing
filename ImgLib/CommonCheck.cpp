// CommonCheck.cpp: implementation of the CommonCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommonCheck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// ��У��
// �����ַ����Ƿ�Ϊ��
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
// ����ֵ��
//  BOOL���գ�����TRUE; �ǿգ�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsEmpty( CString & source ){

	// ȥ�����ҿո�
	source.TrimLeft();
	source.TrimRight();

	return source.IsEmpty();
}

/////////////////////////////////////////////////////////////////////////////
// ��У��
// �����ַ����Ƿ�Ϊ�գ����Ϊ�ո���������ʾ
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString��Ϊ��ʱ�����Ĵ�����ʾ
// ����ֵ��
//  BOOL���գ�����TRUE; �ǿգ�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsEmpty( CString & source, CString message ){

	if( IsEmpty( source ) ){
		AfxMessageBox( message );
		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// ��У��
// �����ַ����Ƿ�Ϊ�գ����Ϊ�ո���������ʾ�����������Ƶ���Ӧ�Ŀؼ�
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString��Ϊ��ʱ�����Ĵ�����ʾ
//  ctrl: CWnd���ַ��������Ŀؼ���Ϊ��ʱ������ת������
// ����ֵ��
//  BOOL���գ�����TRUE; �ǿգ�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsEmpty( CString & source, CString message, CWnd & ctrl ){

	if( IsEmpty( source, message ) == TRUE ){
		ctrl.SetFocus();
		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ���Ϊ����
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
// ����ֵ��
//  BOOL������������TRUE; ��������������FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsInt(CString & source) {

	// ȥ���ո�
	if (!IsEmpty(source))
		return TRUE;//���ַ���������

	int length = source.GetLength();
	LPCSTR str = source.GetString();

	if (!((str[0] == '-'&&length > 1) || (str[0] >= '0'&&str[0] <= '9')))
		return FALSE;
	for (int index = 1; index < length; index++) {
		char num = str[index];
		if (num < '0' || num > '9')
			return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ����Ƿ�Ϊ���������������������������ʾ
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString����������ʱ�����Ĵ�����ʾ
// ����ֵ��
//  BOOL������������TRUE; ��������������FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsInt( CString & source, CString message ){

	if( IsInt( source ) == FALSE ){
		AfxMessageBox(  message );
		return FALSE;
	}
	else{
		return TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ����Ƿ�Ϊ���������������������������ʾ�����������Ƶ���Ӧ�Ŀؼ�
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString����������ʱ�����Ĵ�����ʾ
//  ctrl: CWnd���ַ��������Ŀؼ���Ϊ��ʱ������ת������
// ����ֵ��
//  BOOL������������TRUE; ��������������FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsInt( CString & source, CString message, CWnd & ctrl ){

	if( IsInt( source, message ) == FALSE ){
		ctrl.SetFocus();
		return FALSE;
	}
	else{
		return TRUE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ���Ϊ����
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
// ����ֵ��
//  BOOL�����֣�����TRUE; �������֣�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsNum(CString & source) {

	// ȥ���ո�
	if (IsEmpty(source))
		return TRUE;//���ַ���Ҳ������

	int length = source.GetLength();
	LPCSTR str = source.GetString();

	BOOL isInt = TRUE;

	int index = 0;
	char num = str[index];
	if (num == '-')
	{
		if (length == 1)
			return FALSE;// "-"
		index++;
	}

	num = str[index];
	if (num == '.')
		return FALSE;// ".123" || "-.123"
	else if (num >= '0' && num <= '9')
		index++;
	else
		return FALSE;



	for (; index < length; index++) {

		char num = str[index];

		if (num == '.')
		{
			if (isInt)
				isInt = false;
			else
				return FALSE;// "0.123.123"

			if (index == length - 1)
				return false;// "0."

			continue;
		}

		if (num<'0' || num>'9')
			return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ����Ƿ�Ϊ���֣�����������ָ���������ʾ
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString����������ʱ�����Ĵ�����ʾ
// ����ֵ��
//  BOOL�����֣�����TRUE; �������֣�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsNum( CString & source, CString message ){

	if( IsNum( source ) == FALSE ){
		AfxMessageBox(  message );
		return FALSE;
	}
	else{
		return TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// ����У��
// �����ַ����Ƿ�Ϊ���֣����������������������ʾ�����������Ƶ���Ӧ�Ŀؼ�
// У��Ĺ�����ͬʱȥ���ַ������ߵĿո�
// ������
//  source: CString����У����ַ���;У����Ϻ������߿ո�ȥ��
//  message: CString����������ʱ�����Ĵ�����ʾ
//  ctrl: CWnd���ַ��������Ŀؼ���Ϊ��ʱ������ת������
// ����ֵ��
//  BOOL�����֣�����TRUE; �������֣�����FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsNum( CString & source, CString message, CWnd & ctrl ){

	if( IsNum( source, message ) == FALSE ){
		ctrl.SetFocus();
		return FALSE;
	}
	else{
		return TRUE;
	}
	
}


