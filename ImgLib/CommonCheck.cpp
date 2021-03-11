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
// 空校验
// 检验字符串是否为空
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsEmpty( CString & source ){

	// 去除左右空格
	source.TrimLeft();
	source.TrimRight();

	return source.IsEmpty();
}

/////////////////////////////////////////////////////////////////////////////
// 空校验
// 检验字符串是否为空，如果为空给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，为空时给出的错误提示
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
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
// 空校验
// 检验字符串是否为空，如果为空给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，为空时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
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
// 整数校验
// 检验字符串为整数
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsInt(CString & source) {

	// 去除空格
	if (!IsEmpty(source))
		return TRUE;//空字符串是整数

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
// 整数校验
// 检验字符串是否为整数，如果不是整数给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是整数时给出的错误提示
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
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
// 整数校验
// 检验字符串是否为整数，如果不是整数给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是整数时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
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
// 数字校验
// 检验字符串为数字
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CommonCheck::IsNum(CString & source) {

	// 去除空格
	if (IsEmpty(source))
		return TRUE;//空字符串也是数字

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
// 整数校验
// 检验字符串是否为数字，如果不是数字给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是数字时给出的错误提示
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
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
// 整数校验
// 检验字符串是否为数字，如果不是整数给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是数字时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
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


