#pragma once
//////////////////////////////////////////////////////////////////////////
// DlgShowArray.h : header file
// 显示数组中的图像
// 创建人: 邓飞
// 创建日期: 2008-7-19
/////////////////////////////////////////////////////////////////////////////

#include "ImgLib\BaseColorInfo.h"

class CDlgShowArray : public CDialog
{
// Construction
public:
	CDlgShowArray(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgShowArray)
	enum { IDD = IDD_DLG_SHOW_ARRAY };
	CButton	_staticPos;
	CComboBox	_comboType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShowArray)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShowArray)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonSave();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// 图像数据
	void SetColorData( CBaseColorInfo * colorData );
	// 图像大小
	void SetWidth( int width );
	void SetHeight( int height );

private:
	// 初始化种类下拉框
	void InitComboType();
	// 保存BMP图片
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );
	// 初始化24位BMP数据，由原始图像转换
	void Init24BMP();
	// 刷新24位BMP图像
	void Refresh24BMP();

private:
	// 图像数据
	CBaseColorInfo * _colorData;
	// 图像大小
	int _width;
	int _height;
	// 下拉框类型
	enum COLOR_TYPE{ ALL, RED, GREEN, BLUE } _colorType;

	// 位图数据
	BYTE * _lpBuf;
	// 颜色深度
	int _biBitCount;
	// 头部按钮的位置 
	CRect _headPosRect;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.