//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// 图像处理实验学生平台
// 创建人: 邓飞
// 创建时间: 2008-8-31
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "ImgLib\BaseColorInfo.h"

class CImageStuDlg : public CDialog
{
// Construction
public:
	CImageStuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageStuDlg)
	enum { IDD = IDD_IMAGESTU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageStuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnDestroy();
	afx_msg void OnFileShowArray();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
		// 读取文件头
	BOOL ReadFileHeader( CFile & file );
	// 读取文件信息头
	BOOL ReadInfoHeader( CFile & file );
	// 释放数据
	void FreeData();
	// 计算调色板颜色数量
	int CalcQuadNum();
	// 读取调色板数据
	void ReadQuad( CFile &file );
	// 判断是否为256色灰度图
	BOOL Is256Gray();
	// 读入图像数据
	void ReadImageData( CFile &file );
	// 判断图像类型
	IMAGE_TYPE CalcImageType();
	// 将32位彩色BMP数据转换成24位颜色数据
	void BMPConvertColor32();
	// 将24位彩色BMP数据转换成24位颜色数据
	void BMPConvertColor24();
	// 将8位彩色BMP数据转成24位颜色数据
	void BMPConvertColor8();
	// 将8位灰度BMP数据转成8位灰度数据
	void BMPConvertGray8();
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// 显示图像(通过图像数组, 彩色图像)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// 显示图像(通过图像数组, 灰度图像)
	void ShowPicByArray( int * grayData, int width, int height );

	// 保存BMP图片
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );
	
public:
	// 文件头
	BITMAPFILEHEADER _fileHeader;
	
	// 调色板
	RGBQUAD * _quad;
	// 调色板数目
	int _numQuad;
	// 图像数据
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// 处理后的图像数据
	BYTE * _processBuf;
	// 是否打开了bmp文件
	bool _flag;
	
	// 信息头
	BITMAPINFOHEADER _infoHeader;

	// 图像类型
	IMAGE_TYPE _imageType;
	// 灰度(256灰度数据, 按从上到下, 从左到右的顺序排列,一维矩阵排列)
	int * _grayData;
	// 彩色数据(按从上到下, 从左到右的顺序排列,一维矩阵排列)
	CBaseColorInfo * _colorData;




	afx_msg void OnFullRed();
	afx_msg void OnColorGray();
	afx_msg void OnRedBlue();
	afx_msg void OnGreyWb();
	afx_msg void On32849();
	afx_msg void OnGrayLevel();
	afx_msg void OnMirrorHorizontally();
	afx_msg void OnMirrorVertically();
	afx_msg void OnTransposition();
	afx_msg void OnGrayLevelColorfulVersion();
	afx_msg void OnOnZoomForward();
	afx_msg void OnOnZoomBackward();
	afx_msg void OnLinearInterpolation();
	afx_msg void OnDoubleLinearInterpolation();
	afx_msg void OnGrayNegative();
	afx_msg void OnGrayLog();
	afx_msg void OnGrayPower();
	afx_msg void OnGraySeg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.