//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// ͼ����ʵ��ѧ��ƽ̨
// ������: �˷�
// ����ʱ��: 2008-8-31
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
		// ��ȡ�ļ�ͷ
	BOOL ReadFileHeader( CFile & file );
	// ��ȡ�ļ���Ϣͷ
	BOOL ReadInfoHeader( CFile & file );
	// �ͷ�����
	void FreeData();
	// �����ɫ����ɫ����
	int CalcQuadNum();
	// ��ȡ��ɫ������
	void ReadQuad( CFile &file );
	// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
	BOOL Is256Gray();
	// ����ͼ������
	void ReadImageData( CFile &file );
	// �ж�ͼ������
	IMAGE_TYPE CalcImageType();
	// ��32λ��ɫBMP����ת����24λ��ɫ����
	void BMPConvertColor32();
	// ��24λ��ɫBMP����ת����24λ��ɫ����
	void BMPConvertColor24();
	// ��8λ��ɫBMP����ת��24λ��ɫ����
	void BMPConvertColor8();
	// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
	void BMPConvertGray8();
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// ��ʾͼ��(ͨ��ͼ������, ��ɫͼ��)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
	void ShowPicByArray( int * grayData, int width, int height );

	// ����BMPͼƬ
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );
	
public:
	// �ļ�ͷ
	BITMAPFILEHEADER _fileHeader;
	
	// ��ɫ��
	RGBQUAD * _quad;
	// ��ɫ����Ŀ
	int _numQuad;
	// ͼ������
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// ������ͼ������
	BYTE * _processBuf;
	// �Ƿ����bmp�ļ�
	bool _flag;
	
	// ��Ϣͷ
	BITMAPINFOHEADER _infoHeader;

	// ͼ������
	IMAGE_TYPE _imageType;
	// �Ҷ�(256�Ҷ�����, �����ϵ���, �����ҵ�˳������,һά��������)
	int * _grayData;
	// ��ɫ����(�����ϵ���, �����ҵ�˳������,һά��������)
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