// ImageStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "ImageStuDlg.h"
#include "DlgShowArray.h"
#include "DlgTask.h"
#include <atlimage.h>
#include <afxole.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg dialog

CImageStuDlg::CImageStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageStuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 图像已打开标记
	_flag = false;

}

void CImageStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageStuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageStuDlg, CDialog)
	//{{AFX_MSG_MAP(CImageStuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_FILE_OPEN, OnFileOpen)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_FILE_SHOW_ARRAY, OnFileShowArray)
	ON_COMMAND(IDC_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FULL_RED, &CImageStuDlg::OnFullRed)
	ON_COMMAND(ID_COLOR_GRAY, &CImageStuDlg::OnColorGray)
	ON_COMMAND(ID_RED_BLUE, &CImageStuDlg::OnRedBlue)
	ON_COMMAND(ID_GREY_WB, &CImageStuDlg::OnGreyWb)

	ON_COMMAND(ID_GRAY_LEVEL, &CImageStuDlg::OnGrayLevel)
	ON_COMMAND(ID_MIRROR_HORIZONTALLY, &CImageStuDlg::OnMirrorHorizontally)
	ON_COMMAND(ID_MIRROR_VERTICALLY, &CImageStuDlg::OnMirrorVertically)
	ON_COMMAND(ID_TRANSPOSITION, &CImageStuDlg::OnTransposition)
	ON_COMMAND(ID_GRAY_LEVEL_COLORFUL_VERSION, &CImageStuDlg::OnGrayLevelColorfulVersion)
	ON_COMMAND(ID_ON_ZOOM_FORWARD, &CImageStuDlg::OnOnZoomForward)
	ON_COMMAND(ID_ON_ZOOM_BACKWARD, &CImageStuDlg::OnOnZoomBackward)
	ON_COMMAND(ID_DOUBLE_LINEAR_INTERPOLATION, &CImageStuDlg::OnDoubleLinearInterpolation)
	ON_COMMAND(ID_GRAY_NEGATIVE, &CImageStuDlg::OnGrayNegative)
	ON_COMMAND(ID_GRAY_LOG, &CImageStuDlg::OnGrayLog)
	ON_COMMAND(ID_GRAY_POWER, &CImageStuDlg::OnGrayPower)
	ON_COMMAND(ID_GRAY_SEG, &CImageStuDlg::OnGraySeg)
	ON_COMMAND(ID_JUNPINGHUA, &CImageStuDlg::OnJunpinghua)
	ON_COMMAND(ID_AVERAGE_FILTER, &CImageStuDlg::OnAverageFilter)
	ON_COMMAND(ID_CENTER_MOSAC, &CImageStuDlg::OnCenterMosac)
	ON_COMMAND(ID_WEIGHT_AVERAGE, &CImageStuDlg::OnWeightAverage)
	ON_COMMAND(ID_2D_MIDDLE, &CImageStuDlg::On2dMiddle)
	ON_COMMAND(ID_FAST_AVERAGE, &CImageStuDlg::OnFastAverage)
	ON_COMMAND(ID_FAST_WEIGHT, &CImageStuDlg::OnFastWeight)
	ON_COMMAND(ID_2D_MIDDLE_TEN, &CImageStuDlg::On2dMiddleTen)
	ON_COMMAND(ID_2D_MIDDLE_CROSS, &CImageStuDlg::On2dMiddleCross)
	ON_COMMAND(ID_LAPLACIAN, &CImageStuDlg::OnLaplacian)
	ON_COMMAND(ID_Robert, &CImageStuDlg::OnRobert)
	ON_COMMAND(ID_Sobel, &CImageStuDlg::OnSobel)
	ON_COMMAND(ID_Wallis, &CImageStuDlg::OnWallis)
	ON_COMMAND(ID_RGB_TO_HSI, &CImageStuDlg::OnRgbToHsi)
	ON_COMMAND(ID_RGB_HSI_RGB, &CImageStuDlg::OnRgbHsiRgb)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg message handlers

BOOL CImageStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageStuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageStuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	// 绘图
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// 已经打开文件
		SetDIBitsToDevice(
			  pDC->m_hDC  // 设备描述表
			, 0 // 设备描述表位图输出的起始逻辑x坐标
			, 0 // 设备描述表位图输出的起始逻辑y坐标
			, _infoHeader.biWidth // DIB的宽度
			, _infoHeader.biHeight // DIB的高度
			, 0 // DIB开始读取输出的像素数据的x位置
			, 0 // DIB开始读取输出的像素数据的y位置
			, 0 // DIB中像素的水平行号, 对应lpBits内存缓冲区的第一行数据
			, _infoHeader.biHeight  // DIB的行数
			, _lpBuf  // 像素数据
			, _bitmapInfo //BITMAPINFO数据
			, DIB_RGB_COLORS // 显示的颜色
		);

	}
	ReleaseDC( pDC );

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageStuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// 销毁对话框, 映射WM_DESTORY消息
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	if( _flag == true ){
		FreeData();
	}

	
}

/************************************************************************/
/*                           菜单                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "文件"-->"打开"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen()
{
	// TODO: Add your command handler code here

	LPCTSTR lpszFilter =
		"常见图片格式|*.bmp;*.jpg;*.png;*.gif;*.ico|"
		"BMP Files|*.bmp|"
		"JPEG Files|*.jpg|"
		"PNG Files|*.png|"
		"GIF Files|*.gif|"
		"Icon Files|*.ico|"
		"TIFF Files|*.tif|"
		"WMF Files|*.wmf|"
		"任何文件|*.*|";
	CFileDialog dlg(TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL);
	
	// 打开文件
	if (dlg.DoModal() != IDOK)
		return;

	// 文件名
	CString fileName = dlg.GetPathName();

	CImage image;
	if (image.Load(fileName) != S_OK)
	{
		AfxMessageBox("无法打开文件", MB_OK, MB_ICONERROR);
		return;
	}

	//将任意格式(bmp,jpg,png)的图像通过CImage全部转换为CFile内存流
	COleStreamFile memStream;
	memStream.CreateMemoryStream();
	image.SetHasAlphaChannel(false);
	image.Save(memStream.GetStream(), Gdiplus::ImageFormatBMP);
	memStream.SeekToBegin();
	image.Destroy();



	// 读取文件头
	if (!ReadFileHeader(memStream)) {
		goto END;
	}
	// 读取信息头 
	if (!ReadInfoHeader(memStream)) {
		goto END;
	}

	// 若前面已有文件打开，则释放相应的数据
	if (_flag == true) {
		FreeData();
		_flag = false;
	}

	// 计算调色板颜色数量
	_numQuad = CalcQuadNum();
	// 读取调色板数据
	ReadQuad(memStream);

	// 判断图像类型
	_imageType = CalcImageType();

	// 读入图像数据
	ReadImageData(memStream);




	// 分配处理后的数据
	_processBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;



	Invalidate();

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;

	// 分配空间
	_colorData = new CBaseColorInfo[width * height];
	_grayData = new int[width * height];

	// 根据图像类型，将其转换成相应的图像数据
	if (_imageType == COLOR_32_BIT) {
		BMPConvertColor32();
	}
	else if (_imageType == COLOR_24_BIT) {
		// 24位颜色图像
		BMPConvertColor24();

	}
	else if (_imageType == COLOR_8_BIT) {
		// 256彩色图像
		BMPConvertColor8();
	}
	else if (_imageType == GRAY_8_BIT) {
		// 256灰度图像
		BMPConvertGray8();
		// 将8位灰度数据转成用24位颜色
		Gray8ConvertColor24(_grayData, _colorData, width, height);
	}
	else {
		MessageBox("暂不支持该图像类型");
		// 关闭图像
		FreeData();
		goto END;

	}

	// 图像读取完毕
	_flag = true;
END:
	memStream.Close();

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"显示数组图像"
// 将转换后的24位彩色数据在对话框中显示
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here

	if(_flag == FALSE){
		MessageBox("没有打开图像");
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"保存"菜单
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "没有图片，无法保存" );
		return;
	}
	
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _infoHeader.biWidth, _infoHeader.biHeight, _infoHeader.biBitCount,
			_quad );
	}
	
}



/************************************************************************/
/*                         私有函数                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// 读取文件头
// 参数:
//   file: CFile &, BMP文件
// 返回值:
//   BOOL, TRUE: 成功; FALSE: 失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){

	// 读取文件头
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// 判断是否为BMP文件
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "不是BMP文件", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	// 判断文件是否损坏(文件大小是否与文件头的信息一致)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "文件已损坏", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// 读取文件信息头
// 参数:
//   file: CFile &, 已经打开的BMP文件
// 返回值:
//   BOOL, TRUE成功; 其它失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){

	// 读取文件信息头
	file.Read( &_infoHeader, sizeof( _infoHeader ) );

	// 将图片格式限定在8位图像
// 	if( _infoHeader.biBitCount != 8 ){
// 		AfxMessageBox( "必须为8位灰度图", MB_OK, MB_ICONERROR );
// 		return FALSE;
// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// 释放数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){

	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// 处理后的数据
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// 灰度颜色数据
	delete [] _grayData;
	// 彩色颜色数据
	delete [] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// 计算调色板颜色数量
// 参数: 无
// 返回值:
//   int, 调色板颜色数量
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){

	// 计算调色板数据
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// 相当于2的biBitCount次方
		numQuad = ( 1 << _infoHeader.biBitCount );
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// 读取调色板数据
// 参数:
//   file: CFile &, BMP文件
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){

	// 为图像信息pbi申请空间
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
	);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );

	// 读取调色板
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}

}

//////////////////////////////////////////////////////////////////////////
// 判断是否为256色灰度图
// 判断依据，调色板中所有颜色的的RGB三个分量应该相等
// BOOL: TRUE为256色灰度图
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::Is256Gray(){

	BOOL result = TRUE;
	for( int i = 0; i <= _numQuad - 1; i++ ){
		RGBQUAD color = *( _quad + i );
		//TRACE( "%d: %d, %d, %d\n", i, color.rgbRed,  color.rgbGreen, color.rgbBlue );
		if( !( color.rgbRed == color.rgbGreen && color.rgbRed == color.rgbBlue ) ){
			result = FALSE;
			break;
		}
	}
	
	return result;

}

//////////////////////////////////////////////////////////////////////////
// 读入图像数据
// 参数:
//   file: CFile &, BMP图像
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){

	// 为图像数据申请空间
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// 读取图像数据
	file.Read( _lpBuf, _infoHeader.biSizeImage );

}

//////////////////////////////////////////////////////////////////////////
// 判断图像类型
// 参数: 无
// 返回值: IMAGE_TYPE, 图像类型, 参数枚举IMAGE_TYPE的定义
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType() {

	switch (_infoHeader.biBitCount)
	{
	case IMAGE_TYPE_BIT_32:return COLOR_32_BIT;
	case IMAGE_TYPE_BIT_24:return COLOR_24_BIT;
	case IMAGE_TYPE_BIT_1:return GRAY_1_BIT;
	case IMAGE_TYPE_BIT_8:return Is256Gray() ? GRAY_8_BIT : COLOR_8_BIT;
	default:
		return UNKNOWN_IMAGE_TYPE;
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
// 将BMP数据转换成32位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor32() {

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据

	int i, j;

	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMP图片数据中的坐标
			DWORD index = i * 4 * width + 4 * j;
			if (dwBytes % 4 != 0) {
				index = i * dwBytes + 4 * j;
			}
			// 颜色数组中的坐标
			DWORD resultIndex = (height - 1 - i) * width + j;
			_colorData[resultIndex].SetRed(_lpBuf[index + 2]);
			_colorData[resultIndex].SetGreen(_lpBuf[index + 1]);
			_colorData[resultIndex].SetBlue(_lpBuf[index]);

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将BMP数据转换成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据

	int i,j;

	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位彩色BMP数据转成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_colorData = new CBaseColorInfo[ width * height ];
// 	_colorFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;

			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_colorData[ resultIndex ].SetRed( _quad[ _lpBuf[ index ] ].rgbRed );
			_colorData[ resultIndex ].SetGreen( _quad[ _lpBuf[ index ] ].rgbGreen );
			_colorData[ resultIndex ].SetBlue( _quad[ _lpBuf[ index ] ].rgbBlue );

// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度BMP数据转成8位灰度数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_grayData = new BYTE[ width * height ];
// 	_grayFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;

			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_grayData[ resultIndex ] = _lpBuf[ index ];


// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度数据转成用24位颜色
// 灰度图的RGB值均相同
// 参数:
//   grayData: BYTE *, 灰度数据
//   colorData: CBaseColorInfo *, 24位颜色数据
//   width: 图片宽度
//   height: 图片高度
//  返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::Gray8ConvertColor24( BYTE * grayData, 
										    CBaseColorInfo * colorData, 
											int width, 
											int height ){


	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

// 将8位灰度数据转成用24位颜色
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){

	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组,彩色图像)
// 参数:
//   colorData: CBaseColorInfo, 颜色数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								   int width, 
								   int height ){

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组, 灰度图像)
// 参数:
//   colorData: CBaseColorInfo, 灰度图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								   int width, 
								   int height ){

	// 将灰度图像转成彩色图像
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();

	// 释放彩色图像
	delete [] colorData;

}




//////////////////////////////////////////////////////////////////////////
// 功能：保存BMP图片
// 参数：
//   bmpName: char *, 文件名(含路径、文件后缀)
//   imgBuf: unsigned char *, 图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//   biBitCount: int, 像素深度
//   pColorTable: RGBAUAD *, 颜色表
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							  unsigned char * imgBuf, 
							  int width, 
							  int height,
							  int biBitCount, 
							  RGBQUAD * pColorTable 
							 ){
	
	// 如果位图数据为空，则没有数据传入
	if( !imgBuf ){
		return false;
	}
	
	// 颜色表大小，以字节为单位，灰度图像颜色表为1024，彩色图像颜色表大小为0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // 感觉不一定正确
	} 
	
	// 将带存储图像数据每行字节数转为4的倍数
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// 以二进制的写的方式打开文件
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// 申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp类型
	// bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // 图像数据字节数
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits是图像文件前三部分所需空间之和
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// 文件头写入文件
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// 申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // 位图信息头结构的大小(40个字节)
	head.biWidth = width;// 图像宽度，以像素为单位
	head.biHeight = height;// 图像高度，以像素为单位
	head.biPlanes = 1;// 必须为1
	head.biBitCount = biBitCount; // 像素深度，每个像素的为数(bit数)
	head.biCompression = BI_RGB; // 图像是否压缩，一般是未压缩的
	head.biSizeImage = lineByte * height; // 实际的位图数据占据的字节数
	head.biXPelsPerMeter = 0; // 目标设备的水平分辨率
	head.biYPelsPerMeter = 0; // 目标设备的垂直分辨率
	head.biClrUsed = 0; // 本图像实际用到的颜色数
	head.biClrImportant = 0; // 本图像重要的颜色，如果为0，则所有的颜色均重要 
	
	// 写位图信息头进内存
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// 如果图像时灰度图像，有颜色表，写入文件
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// 写位图数据进文件
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// 关闭文件
	fclose( fp );
	
	return true;
	
}






void CImageStuDlg::OnFullRed()
{
	// TODO: 在此添加命令处理程序代码
	int width = 800;
	int height = 600;
	///生成图像
	CBaseColorInfo * img = new CBaseColorInfo[width * height];
	//数据
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			img[index] = CBaseColorInfo(255, 0, 0);
		}
	}
	//显示
	ShowPicByArray(img, width, height);

	//释放
	delete[] img;
	//MessageBox("test");
}


void CImageStuDlg::OnColorGray()
{
	// TODO: 在此添加命令处理程序代码
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图像
	CBaseColorInfo * img = new CBaseColorInfo[size];
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			CBaseColorInfo oldInfo = _colorData[index];
			int gray = 0.299 * oldInfo.GetRed()
				+ 0.587 * oldInfo.GetGreen()
				+ 0.114 * oldInfo.GetBlue();
			CBaseColorInfo newInfo = CBaseColorInfo(
				gray, gray, gray
			);
			img[index] = newInfo;
		}
	}
	//显示
	ShowPicByArray(img, width, height);

	//释放
	delete[] img;
}

void CImageStuDlg::OnRedBlue()
{
	// TODO: 在此添加命令处理程序代码
	int width = 800;
	int height = 600;
	///生成图像
	CBaseColorInfo * img = new CBaseColorInfo[width * height];
	//数据
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			if (((x / 40) % 2 + (y / 30) % 2) % 2) {
				img[index] = CBaseColorInfo(255, 0, 0);
			}
			else {
				img[index] = CBaseColorInfo(0, 0, 255);
			}
		}
	}
	//显示
	ShowPicByArray(img, width, height);

	//释放
	delete[] img;
	//MessageBox("test");
}

void CImageStuDlg::OnGreyWb()
{
	// TODO: 在此添加命令处理程序代码
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//生成图像
	int * img = new int[size];
	//设置阈值
	int limit = 140;
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			int oldGray = _grayData[index];
			int newGray = oldGray;
			if (oldGray > limit) {
				newGray = 255;
			}
			else newGray = 0;
			img[index] = newGray;
		}
	}
	
	//显示
	ShowPicByArray(img, width, height);

	//释放
	delete[] img;
}

//灰度图像灰度级分辨率
void CImageStuDlg::OnGrayLevel()
{
	//创建图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	//计算
	int level_count = 8; //代表灰度级数
	int step = GRAY_LEVEL_256 / level_count;
	int rule[GRAY_LEVEL_256] = { 0 };

	///这种就比较快，因为灰度只有256级，每个你都做个映射就好了
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = int(i / step) * step;
	}
	for (int i = 0; i < size; ++i) {
		int gray = _grayData[i];
		img[i] = rule[gray];
	}
	/*
	这种方式计算量为 像素点*2，在像素点教多的情况下会比较慢，所以可以空间换时间
	for (int i = 0; i < size; ++i) {
		int gray = _grayData[i];
		img[i] = int(gray / step) * step;
	}
	*/
	//显示
	ShowPicByArray(img, width, height);
	//删除资源
	if (img != NULL)
		delete[] img;

}

void CImageStuDlg::OnGrayLevelColorfulVersion()
{
	//创建图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[width * height];

	//计算
	int level_count = 8; //代表灰度级数
	int COLOR_LEVEL = 256;
	int step = COLOR_LEVEL / level_count;

	//这种方式计算量为 像素点*2，在像素点教多的情况下会比较慢，所以可以空间换时间
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			CBaseColorInfo oldInfo = _colorData[index];
			CBaseColorInfo newInfo = CBaseColorInfo(
				int((oldInfo.GetRed()+50) / step) * step, 
				int((oldInfo.GetGreen()+75) / step) * step, 
				int((oldInfo.GetBlue()+150) / step) * step
			);
			img[index] = newInfo;
		}
	}
	//显示
	ShowPicByArray(img, width, height);
	//删除资源
	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnMirrorHorizontally()
{
	//创建图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// 水平镜像
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			//对称坐标
			int oldX = width - 1 - x;
			int oldY = y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//显示
	ShowPicByArray(img, width, height);
	//删除资源
	if (img != NULL)
		delete[] img;

}

void CImageStuDlg::OnMirrorVertically()
{
	//创建图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// 垂直镜像
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			//对称坐标
			int oldX = x;
			int oldY = height - 1 - y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//显示
	ShowPicByArray(img, width, height);
	//删除资源
	if (img != NULL)
		delete[] img;
}

void CImageStuDlg::OnTransposition()
{
	//创建图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// 转置
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = x * height + y;
			//对称坐标
			int oldX = width - x;
			int oldY =  y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//显示
	ShowPicByArray(img, height, width);
	//删除资源
	if (img != NULL)
		delete[] img;
}



//前向映射
void CImageStuDlg::OnOnZoomForward()
{
	double scale = 1.2;
	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;
	int width = oldwidth * scale;
	int height = oldheight * scale;
	int size = width * height;
	int *img = new int[size];

	for (int x = 0; x < oldwidth; ++x) {
		for (int y = 0; y < oldheight; ++y) {
			int oldIndex = y * oldwidth + x;
			int newX = x * scale;
			int newY = y * scale;
			int newIndex = newY * width + newX;
			img[newIndex] = _grayData[oldIndex];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnOnZoomBackward()
{
	double scale = 2.0;
	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;
	int width = oldwidth * scale;
	int height = oldheight * scale;
	int size = width * height;
	int *img = new int[size];

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int newIndex = y * width + x;
			int oldX = x / scale;
			int oldY = y / scale;
			int oldIndex = oldY * oldwidth + oldX;
			img[newIndex] = _grayData[oldIndex];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//二次线性插值
void CImageStuDlg::OnDoubleLinearInterpolation()
{
	double scale = 2.0;
	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;
	int width = oldwidth * scale;
	int height = oldheight * scale;
	int size = width * height;
	int *img = new int[size];

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int newIndex = y * width + x;
			double oldX = x / scale;
			double oldY = y / scale;
			//ga
			int aX = oldX;
			int aY = oldY;
			int aIndex = aY * oldwidth + aX;
			int ga = _grayData[aIndex];
			//gb
			int bX = min(oldX + 1, oldwidth-1);
			int bY = oldY;
			int bIndex = bY * oldwidth + bX;
			int gb = _grayData[bIndex];
			//ge
			double ge = (oldX - aX) * (gb - ga) + ga;
			//gc
			int cX = oldX;
			int cY = min(oldY + 1, oldheight-1);
			int cIndex = cY * oldwidth + cX;
			int gc = _grayData[cIndex];
			//gd
			int dX = min(oldX + 1, oldwidth-1);
			int dY = min(oldY + 1, oldheight-1);
			int dIndex = dY * oldwidth + dX;
			int gd = _grayData[dIndex];
			//gf
			double gf = (oldX - cX) * (gd - gc) + gc;

			int newGray = (oldY - aY) * (gf - ge) + ge;

			img[newIndex] = newGray;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//灰度取反
void CImageStuDlg::OnGrayNegative()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int rule[GRAY_LEVEL_256] = { 0 };
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = 255 - i;
	}
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			img[index] = rule[_grayData[index]];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//对数变换
void CImageStuDlg::OnGrayLog()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int rule[GRAY_LEVEL_256] = { 0 };
	int factor = 100;
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = factor * log(i + 0.5);
	}
	double k = 255.0 / (double)rule[255];
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			img[index] = rule[_grayData[index]] * k;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//幂次变换
void CImageStuDlg::OnGrayPower()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int rule[GRAY_LEVEL_256] = { 0 };
	int factor = 100;
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = factor * pow(i, 3);
	}
	double k = 255.0 / (double)rule[255];
	for (int i = 0; i < size; ++i) {
		img[i] = k * rule[_grayData[i]];
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnGraySeg()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int rule[GRAY_LEVEL_256] = { 0 };
	int range1 = 100;
	int range2 = 200;
	int factor = 100;
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		if (i < range1) {
			
			rule[i] = i;
		}
		else if (i < range2) {
			rule[i] = factor * log(i-100);
		}
		else {
			rule[i] = pow(i, 0.3);
		}
	}

	for (int i = 0; i < size; ++i) {
		img[i] = rule[_grayData[i]];
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//均平化
void CImageStuDlg::OnJunpinghua()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	//计算映射规则
	int rule[GRAY_LEVEL_256] = { 0 };

	//直方图
	int zhifangtu[GRAY_LEVEL_256] = { 0 };
	for (int i = 0; i < size; ++i) {
		zhifangtu[_grayData[i]]++;
	}
	/*
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		CString str;
		str.Format("%d, %d\n", i, zhifangtu[i]);
		::OutputDebugString(str);
	}
	 */
	//归一化
	double guiyihua[GRAY_LEVEL_256] = { 0.0 };
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		guiyihua[i] = zhifangtu[i] * 1.0 / (double)size;
	}
	/*
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		CString str;
		str.Format("%d, %lf\n", i, guiyihua[i]);
		::OutputDebugString(str);
	}
	*/
	// 累积
	double leiji[GRAY_LEVEL_256] = { 0,0 };
	leiji[0] = guiyihua[0];
	for (int i = 1; i < GRAY_LEVEL_256; ++i) {
		leiji[i] = guiyihua[i] + leiji[i - 1];
	}
	/*
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		CString str;
		str.Format("%d, %lf\n", i, leiji[i]);
		::OutputDebugString(str);
	}
	*/
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = (int)(leiji[i] * (GRAY_LEVEL_256 - 1) + 0.5);
	}
	for (int i = 0; i < size; ++i) {
		img[i] = rule[_grayData[i]];
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//邻域平均
void CImageStuDlg::OnAverageFilter()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int N = 10;
	int radius = N / 2;
	int factor = N * N;
	for (int x = radius; x < width - radius; ++ x) {
		for (int y = radius; y < height - radius; ++ y) {
			int index = y * width + x;
			//取邻域，求和
			int sum = 0;
			for (int m = x - radius; m <= x + radius; ++ m) {
				for (int n = y - radius; n <= y + radius; ++ n) {
					int oldIndex = n * width + m;
					sum += _grayData[oldIndex];
				}
			}
			int gray = sum / (factor);
			img[index] = gray;
		}
	}
	
	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//中心马赛克
void CImageStuDlg::OnCenterMosac()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int N = 40;
	int radius = N / 2;
	int factor = N * N;
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			img[y * width + x] = _grayData[y * width + x];
		}
	}
	for (int x = width / 4 + radius; x < width * 3 / 4 - radius; ++x) {
		for (int y = height / 4 + radius; y < height * 3 / 4 - radius; ++y) {
			int index = y * width + x;
			//取邻域，求和
			int sum = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				for (int n = y - radius; n <= y + radius; ++n) {
					int oldIndex = n * width + m;
					sum += _grayData[oldIndex];
				}
			}
			int gray = sum / (factor);
			img[index] = gray;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//加权平均
void CImageStuDlg::OnWeightAverage()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int N = 3;
	int radius = N / 2;
	int factor = N * N;
	int model[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1};
	int neighbor[9] = {0};
	for (int x = radius; x < width - radius; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int index = y * width + x;
			//取邻域
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				for (int n = y - radius; n <= y + radius; ++n) {
					int oldIndex = n * width + m;
					neighbor[order++] = _grayData[oldIndex];

				}
			}
			//求和
			int sum = 0;
			for (int i = 0; i < 9; ++ i) {
				sum += neighbor[i] * model[i];
			}
			int gray = sum / 16;
			img[index] = gray;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


//快速邻域平均
void CImageStuDlg::OnFastAverage()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int *horizontal = new int[size];
	for (int i = 0; i < size; ++i) {
		horizontal[i] = _grayData[i];
	}

	int N = 5;
	int radius = N / 2;

	for (int y = 0; y < height; ++y) {
		for (int x = radius; x < width - radius; ++x) {
			int sum = 0;
			int n = y;
			for (int m = x - radius; m <= x + radius; ++m) {
				int index = n * width + m;
				sum += _grayData[index];
			}
			int horizontal_index = y * width + x;
			horizontal[horizontal_index] = sum / N;
		}
	}

	for (int x = 0; x < width; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int sum = 0;
			int m = x;
			for (int n = y - radius; n <= y + radius; ++n) {
				int index = n * width + m;
				sum += horizontal[index];
			}
			int result_index = y * width + x;
			img[result_index] = sum / N;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//快速加权平均
void CImageStuDlg::OnFastWeight()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int *horizontal = new int[size];
	for (int i = 0; i < size; ++i) {
		horizontal[i] = _grayData[i];
	}

	int N = 5;
	int radius = N / 2;
	int weight[] = {1,1,2,4,6,10,6,4,2,1,1};
	for (int y = 0; y < height; ++y) {
		for (int x = radius; x < width - radius; ++x) {
			int sum = 0;
			int n = y;
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				int index = n * width + m;
				sum += _grayData[index] * weight[order++];
			}
			int horizontal_index = y * width + x;
			horizontal[horizontal_index] = sum / 38/*权值重数组和*/;
		}
	}

	for (int x = 0; x < width; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int sum = 0;
			int m = x;
			int order = 0;
			for (int n = y - radius; n <= y + radius; ++n) {
				int index = n * width + m;
				sum += horizontal[index] * weight[order++];
			}
			int result_index = y * width + x;
			img[result_index] = sum / N;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//2D中值(周围)
void CImageStuDlg::On2dMiddle()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int radius = 2;
	int neighbor[1000] = { 0 };
	int neighborsz = (2 * radius + 1)*(2 * radius + 1);
	for (int x = radius; x < width - radius; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int index = y * width + x;
			//取邻域
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				for (int n = y - radius; n <= y + radius; ++n) {
					int oldIndex = n * width + m;
					neighbor[order++] = _grayData[oldIndex];
				}
			}
			//排序
			std::stable_sort(neighbor, neighbor + neighborsz);
			//赋值
			img[index] = neighbor[neighborsz / 2];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

void CImageStuDlg::On2dMiddleTen()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int radius = 2;
	int neighbor[1000] = { 0 };
	int neighborsz = 2 * 2 * radius - 1;
	for (int x = radius; x < width - radius; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int index = y * width + x;
			//取邻域(十字
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				int oldIndex = y * width + m;
				neighbor[order++] = _grayData[oldIndex];
			}
			for (int n = y - radius; n <= y + radius; ++n) {
				int oldIndex = n * width + x;
				if (n == y) continue;
				neighbor[order++] = _grayData[oldIndex];
			}
			//排序
			std::stable_sort(neighbor, neighbor + neighborsz);
			//赋值
			img[index] = neighbor[neighborsz / 2];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

void CImageStuDlg::On2dMiddleCross()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int radius = 2;
	int neighbor[1000] = { 0 };
	int neighborsz = 2 * 2 * radius - 1;
	for (int x = radius; x < width - radius; ++x) {
		for (int y = radius; y < height - radius; ++y) {
			int index = y * width + x;
			//取邻域(交叉
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				int oldIndex = (y + (m - x)) * width + m;
				neighbor[order++] = _grayData[oldIndex];
			}
			for (int n = y - radius; n <= y + radius; ++n) {
				int oldIndex = n * width + x - (n - y);
				if (n == y) continue;
				neighbor[order++] = _grayData[oldIndex];
			}
			//排序
			std::stable_sort(neighbor, neighbor + neighborsz);
			//赋值
			img[index] = neighbor[neighborsz / 2];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//拉普拉斯算子
void CImageStuDlg::OnLaplacian()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];
	int dic[8][2] = {1,0, 0,1, -1,0, -1,1, 0,-1, 1,-1, 1,1, -1,-1};
	for (int x = 1; x < width - 1; ++ x) {
		for (int y = 1; y < height - 1; ++ y) {
			int index = y * width + x;
			int gray = -8 * _grayData[index];
			for (int k = 0; k < 8; ++k) {
				int _pos = (y + dic[k][0]) * width + x + dic[k][1];
				gray += _grayData[_pos];
			}
			if (gray < 0) gray = -gray;
			img[index] = gray;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnRobert()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];
	
	int neighbor[4] = { 0 };

	int model_x[4] = { -1, 0, 0, 1 };

	int model_y[4] = { 0, -1, 1, 0 };

	for (int x = 1; x < width - 1; ++x) {
		for (int y = 1; y < height - 1; ++y) {
			int order = 0;
			for (int m = x; m <= x + 1; ++m) {
				for (int n = y; n <= y + 1; ++n) {
					int tempIndex = n * width + m;
					neighbor[order] = _grayData[tempIndex];
					++order;
				}
			}
			int index = y * width + x;

			int sum_x = 0;
			for (int i = 0; i < 4; ++i) {
				sum_x += neighbor[i] * model_x[i];
			}
			if (sum_x < 0) sum_x = -sum_x;
			int sum_y = 0;
			for (int i = 0; i < 4; ++i) {
				sum_y += neighbor[i] * model_y[i];
			}
			if (sum_y < 0) sum_y = -sum_y;

			img[index] = sum_x + sum_y;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnSobel()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	int neighbor[9] = { 0 };

	int model_x[9] = { -1, -2, -1,
						0, 0, 0,
						1, 2, 1  };

	int model_y[9] = { -1, 0, 1,
						-2, 0, 2,
						-1, 0, 1 };

	for (int x = 1; x < width - 1; ++x) {
		for (int y = 1; y < height - 1; ++y) {
			int order = 0;
			for (int m = x-1; m <= x + 1; ++m) {
				for (int n = y-1; n <= y + 1; ++n) {
					int tempIndex = n * width + m;
					neighbor[order] = _grayData[tempIndex];
					++order;
				}
			}
			int index = y * width + x;

			int sum_x = 0;
			for (int i = 0; i < 9; ++i) {
				sum_x += neighbor[i] * model_x[i];
			}
			if (sum_x < 0) sum_x = -sum_x;
			int sum_y = 0;
			for (int i = 0; i < 9; ++i) {
				sum_y += neighbor[i] * model_y[i];
			}
			if (sum_y < 0) sum_y = -sum_y;

			img[index] = sum_x + sum_y;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnWallis()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	for (int x = 1; x < width - 1; ++x) {
		for (int y = 1; y < height - 1; ++y) {
			int order = 0;
			
			int index = y * width + x;
			int gray = 46 * (
				5 * log(_grayData[index] + 1)
				- (log(_grayData[index - 1] + 1)
				+ log(_grayData[index + 1] + 1)
				+ log(_grayData[index - width] + 1)
				+ log(_grayData[index + width] + 1))
				);

			img[index] = gray;
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnRgbToHsi()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	const double pi = acos(-1.0);
	CBaseColorInfo  *img = new CBaseColorInfo[size];

	for (int index = 0; index < size; ++index) {
		CBaseColorInfo info = _colorData[index];
		// 归一化
		double red= info.GetRed();
		double green = info.GetGreen();
		double blue = info.GetBlue();

		if (red == green && red == blue) {
			img[index] = CBaseColorInfo(0, 0, red);
		}
		else {
			// 计算S
			double r = red / 255;
			double b = blue / 255;
			double g = green / 255;
			double i = (r + g + b) / 3;
			double min = r;
 			if (min > g) {
				min = g;
			}
			if (min > b) {
				min = b;
			}
			double s = 1 - 3 / (r + g + b) * min;

			//计算H
			double son = ((r - g) + (r - b)) / 2;
			double mother = sqrt ((r - g) * (r - g) + (r - b) * (g - b));
			double angle = acos(son / mother);
			double h = angle;
			if (b > g) {
				h = pi * 2 - angle;
			}
			img[index] = CBaseColorInfo(h / (2 * pi) * 255, s * 255, i * 255);
		}
		
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnRgbHsiRgb()
{
	// TODO: 在此添加命令处理程序代码
		//生成图像
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo* img = new CBaseColorInfo[size];

	const double PI = 3.1415926;
	const double PI_2 = 2 * PI;

	//计算
	for (int x = 0; x < size; ++x) {
		//r, g, b -->hsi
		CBaseColorInfo info = _colorData[x];
		// 归一化
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;

		//计算
		double i = (r + g + b) / 3.0;
		double h = 0.0;
		double s = 0.0;
		if (info.GetRed() == info.GetBlue() && info.GetGreen() == info.GetBlue()) {
			//灰度图
			h = 0.0;
			s = 0.0;
		}
		else {
			//计算s
			//1）求出最小值
			double min = r;
			if (min > g) {
				min = g;
			}
			if (min > b) {
				min = b;
			}
			s = 1 - 3 * (min / (r + g + b));

			//计算h
			double son = ((r - g) + (r - b)) / 2;
			double mom = sqrt((r - g) * (r - g) + (r - b) * (g - b));
			double angle = acos(son / mom);

			if (b <= g) {
				h = angle;
			}
			else {
				h = PI_2 - angle;
			}
		}

			h = h / PI_2 * 360;

		//饱和度
		//s = 0;

		//亮度
		i = i * 255;

		if ( h <= 120) {
			h = h / 360.0 * PI_2;
			r = i * (1 + s * cos(h) / cos(PI / 3.0 - h));
			b = i * (1 - s);
			g = 3 * i - (b + r);
		}
		else if (h <= 240) {
			h = h / 360.0 * PI_2;
			g = i * (1 + s * cos(h - PI * 2.0 / 3.0) / cos(PI - h));
			r = i * (1 - s);
			b = 3 * i - (g + r);
		}
		else {
			h = h / 360.0 * PI_2;
			b = i * (1 + s * cos(h - PI * 4.0 / 3.0) / cos(PI * 5.0 / 3.0 - h));
			g = i * (1 - s);
			r = 3 * i - (g + b);
		}
		//重新映射到[0, 255]
		img[x] = CBaseColorInfo(r, g, b);
	}
	//显示
	ShowPicByArray(img, width, height);

	//删除
	if (img != NULL) 
		delete[] img;
	
}
