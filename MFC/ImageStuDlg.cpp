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

	// ͼ���Ѵ򿪱��
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

	// ��ͼ
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// �Ѿ����ļ�
		SetDIBitsToDevice(
			  pDC->m_hDC  // �豸������
			, 0 // �豸������λͼ�������ʼ�߼�x����
			, 0 // �豸������λͼ�������ʼ�߼�y����
			, _infoHeader.biWidth // DIB�Ŀ��
			, _infoHeader.biHeight // DIB�ĸ߶�
			, 0 // DIB��ʼ��ȡ������������ݵ�xλ��
			, 0 // DIB��ʼ��ȡ������������ݵ�yλ��
			, 0 // DIB�����ص�ˮƽ�к�, ��ӦlpBits�ڴ滺�����ĵ�һ������
			, _infoHeader.biHeight  // DIB������
			, _lpBuf  // ��������
			, _bitmapInfo //BITMAPINFO����
			, DIB_RGB_COLORS // ��ʾ����ɫ
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
// ���ٶԻ���, ӳ��WM_DESTORY��Ϣ
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
/*                           �˵�                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen()
{
	// TODO: Add your command handler code here

	LPCTSTR lpszFilter =
		"����ͼƬ��ʽ|*.bmp;*.jpg;*.png;*.gif;*.ico|"
		"BMP Files|*.bmp|"
		"JPEG Files|*.jpg|"
		"PNG Files|*.png|"
		"GIF Files|*.gif|"
		"Icon Files|*.ico|"
		"TIFF Files|*.tif|"
		"WMF Files|*.wmf|"
		"�κ��ļ�|*.*|";
	CFileDialog dlg(TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL);
	
	// ���ļ�
	if (dlg.DoModal() != IDOK)
		return;

	// �ļ���
	CString fileName = dlg.GetPathName();

	CImage image;
	if (image.Load(fileName) != S_OK)
	{
		AfxMessageBox("�޷����ļ�", MB_OK, MB_ICONERROR);
		return;
	}

	//�������ʽ(bmp,jpg,png)��ͼ��ͨ��CImageȫ��ת��ΪCFile�ڴ���
	COleStreamFile memStream;
	memStream.CreateMemoryStream();
	image.SetHasAlphaChannel(false);
	image.Save(memStream.GetStream(), Gdiplus::ImageFormatBMP);
	memStream.SeekToBegin();
	image.Destroy();



	// ��ȡ�ļ�ͷ
	if (!ReadFileHeader(memStream)) {
		goto END;
	}
	// ��ȡ��Ϣͷ 
	if (!ReadInfoHeader(memStream)) {
		goto END;
	}

	// ��ǰ�������ļ��򿪣����ͷ���Ӧ������
	if (_flag == true) {
		FreeData();
		_flag = false;
	}

	// �����ɫ����ɫ����
	_numQuad = CalcQuadNum();
	// ��ȡ��ɫ������
	ReadQuad(memStream);

	// �ж�ͼ������
	_imageType = CalcImageType();

	// ����ͼ������
	ReadImageData(memStream);




	// ���䴦��������
	_processBuf = (BYTE *)HeapAlloc(GetProcessHeap(), 0, _infoHeader.biSizeImage);

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;



	Invalidate();

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;

	// ����ռ�
	_colorData = new CBaseColorInfo[width * height];
	_grayData = new int[width * height];

	// ����ͼ�����ͣ�����ת������Ӧ��ͼ������
	if (_imageType == COLOR_32_BIT) {
		BMPConvertColor32();
	}
	else if (_imageType == COLOR_24_BIT) {
		// 24λ��ɫͼ��
		BMPConvertColor24();

	}
	else if (_imageType == COLOR_8_BIT) {
		// 256��ɫͼ��
		BMPConvertColor8();
	}
	else if (_imageType == GRAY_8_BIT) {
		// 256�Ҷ�ͼ��
		BMPConvertGray8();
		// ��8λ�Ҷ�����ת����24λ��ɫ
		Gray8ConvertColor24(_grayData, _colorData, width, height);
	}
	else {
		MessageBox("�ݲ�֧�ָ�ͼ������");
		// �ر�ͼ��
		FreeData();
		goto END;

	}

	// ͼ���ȡ���
	_flag = true;
END:
	memStream.Close();

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��ʾ����ͼ��"
// ��ת�����24λ��ɫ�����ڶԻ�������ʾ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here

	if(_flag == FALSE){
		MessageBox("û�д�ͼ��");
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"����"�˵�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "û��ͼƬ���޷�����" );
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
/*                         ˽�к���                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ�ͷ
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ:
//   BOOL, TRUE: �ɹ�; FALSE: ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){

	// ��ȡ�ļ�ͷ
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// �ж��Ƿ�ΪBMP�ļ�
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "����BMP�ļ�", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	// �ж��ļ��Ƿ���(�ļ���С�Ƿ����ļ�ͷ����Ϣһ��)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "�ļ�����", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ���Ϣͷ
// ����:
//   file: CFile &, �Ѿ��򿪵�BMP�ļ�
// ����ֵ:
//   BOOL, TRUE�ɹ�; ����ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){

	// ��ȡ�ļ���Ϣͷ
	file.Read( &_infoHeader, sizeof( _infoHeader ) );

	// ��ͼƬ��ʽ�޶���8λͼ��
// 	if( _infoHeader.biBitCount != 8 ){
// 		AfxMessageBox( "����Ϊ8λ�Ҷ�ͼ", MB_OK, MB_ICONERROR );
// 		return FALSE;
// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// �ͷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){

	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// ����������
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// �Ҷ���ɫ����
	delete [] _grayData;
	// ��ɫ��ɫ����
	delete [] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// �����ɫ����ɫ����
// ����: ��
// ����ֵ:
//   int, ��ɫ����ɫ����
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){

	// �����ɫ������
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// �൱��2��biBitCount�η�
		numQuad = ( 1 << _infoHeader.biBitCount );
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// ��ȡ��ɫ������
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){

	// Ϊͼ����Ϣpbi����ռ�
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
	);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );

	// ��ȡ��ɫ��
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}

}

//////////////////////////////////////////////////////////////////////////
// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
// �ж����ݣ���ɫ����������ɫ�ĵ�RGB��������Ӧ�����
// BOOL: TRUEΪ256ɫ�Ҷ�ͼ
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
// ����ͼ������
// ����:
//   file: CFile &, BMPͼ��
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){

	// Ϊͼ����������ռ�
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// ��ȡͼ������
	file.Read( _lpBuf, _infoHeader.biSizeImage );

}

//////////////////////////////////////////////////////////////////////////
// �ж�ͼ������
// ����: ��
// ����ֵ: IMAGE_TYPE, ͼ������, ����ö��IMAGE_TYPE�Ķ���
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
// ��BMP����ת����32λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor32() {

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if (((DWORD)_infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����

	int i, j;

	for (i = 0; i <= height - 1; i++) {
		for (j = 0; j <= width - 1; j++) {

			// BMPͼƬ�����е�����
			DWORD index = i * 4 * width + 4 * j;
			if (dwBytes % 4 != 0) {
				index = i * dwBytes + 4 * j;
			}
			// ��ɫ�����е�����
			DWORD resultIndex = (height - 1 - i) * width + j;
			_colorData[resultIndex].SetRed(_lpBuf[index + 2]);
			_colorData[resultIndex].SetGreen(_lpBuf[index + 1]);
			_colorData[resultIndex].SetBlue(_lpBuf[index]);

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��BMP����ת����24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����

	int i,j;

	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// ��ɫ�����е�����
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ��ɫBMP����ת��24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
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
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;

			// ��ɫ�����е�����
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
// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
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
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;

			// ��ɫ�����е�����
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
// ��8λ�Ҷ�����ת����24λ��ɫ
// �Ҷ�ͼ��RGBֵ����ͬ
// ����:
//   grayData: BYTE *, �Ҷ�����
//   colorData: CBaseColorInfo *, 24λ��ɫ����
//   width: ͼƬ���
//   height: ͼƬ�߶�
//  ����ֵ: ��
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

// ��8λ�Ҷ�����ת����24λ��ɫ
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){

	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������,��ɫͼ��)
// ����:
//   colorData: CBaseColorInfo, ��ɫ����
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								   int width, 
								   int height ){

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
// ����:
//   colorData: CBaseColorInfo, �Ҷ�ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								   int width, 
								   int height ){

	// ���Ҷ�ͼ��ת�ɲ�ɫͼ��
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();

	// �ͷŲ�ɫͼ��
	delete [] colorData;

}




//////////////////////////////////////////////////////////////////////////
// ���ܣ�����BMPͼƬ
// ������
//   bmpName: char *, �ļ���(��·�����ļ���׺)
//   imgBuf: unsigned char *, ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//   biBitCount: int, �������
//   pColorTable: RGBAUAD *, ��ɫ��
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							  unsigned char * imgBuf, 
							  int width, 
							  int height,
							  int biBitCount, 
							  RGBQUAD * pColorTable 
							 ){
	
	// ���λͼ����Ϊ�գ���û�����ݴ���
	if( !imgBuf ){
		return false;
	}
	
	// ��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024����ɫͼ����ɫ���СΪ0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // �о���һ����ȷ
	} 
	
	// �����洢ͼ������ÿ���ֽ���תΪ4�ı���
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// �Զ����Ƶ�д�ķ�ʽ���ļ�
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// ����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp����
	// bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // ͼ�������ֽ���
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits��ͼ���ļ�ǰ����������ռ�֮��
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// �ļ�ͷд���ļ�
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// ����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // λͼ��Ϣͷ�ṹ�Ĵ�С(40���ֽ�)
	head.biWidth = width;// ͼ���ȣ�������Ϊ��λ
	head.biHeight = height;// ͼ��߶ȣ�������Ϊ��λ
	head.biPlanes = 1;// ����Ϊ1
	head.biBitCount = biBitCount; // ������ȣ�ÿ�����ص�Ϊ��(bit��)
	head.biCompression = BI_RGB; // ͼ���Ƿ�ѹ����һ����δѹ����
	head.biSizeImage = lineByte * height; // ʵ�ʵ�λͼ����ռ�ݵ��ֽ���
	head.biXPelsPerMeter = 0; // Ŀ���豸��ˮƽ�ֱ���
	head.biYPelsPerMeter = 0; // Ŀ���豸�Ĵ�ֱ�ֱ���
	head.biClrUsed = 0; // ��ͼ��ʵ���õ�����ɫ��
	head.biClrImportant = 0; // ��ͼ����Ҫ����ɫ�����Ϊ0�������е���ɫ����Ҫ 
	
	// дλͼ��Ϣͷ���ڴ�
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// ���ͼ��ʱ�Ҷ�ͼ������ɫ��д���ļ�
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// дλͼ���ݽ��ļ�
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// �ر��ļ�
	fclose( fp );
	
	return true;
	
}






void CImageStuDlg::OnFullRed()
{
	// TODO: �ڴ���������������
	int width = 800;
	int height = 600;
	///����ͼ��
	CBaseColorInfo * img = new CBaseColorInfo[width * height];
	//����
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			img[index] = CBaseColorInfo(255, 0, 0);
		}
	}
	//��ʾ
	ShowPicByArray(img, width, height);

	//�ͷ�
	delete[] img;
	//MessageBox("test");
}


void CImageStuDlg::OnColorGray()
{
	// TODO: �ڴ���������������
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼ��
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
	//��ʾ
	ShowPicByArray(img, width, height);

	//�ͷ�
	delete[] img;
}

void CImageStuDlg::OnRedBlue()
{
	// TODO: �ڴ���������������
	int width = 800;
	int height = 600;
	///����ͼ��
	CBaseColorInfo * img = new CBaseColorInfo[width * height];
	//����
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
	//��ʾ
	ShowPicByArray(img, width, height);

	//�ͷ�
	delete[] img;
	//MessageBox("test");
}

void CImageStuDlg::OnGreyWb()
{
	// TODO: �ڴ���������������
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	//����ͼ��
	int * img = new int[size];
	//������ֵ
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
	
	//��ʾ
	ShowPicByArray(img, width, height);

	//�ͷ�
	delete[] img;
}

//�Ҷ�ͼ��Ҷȼ��ֱ���
void CImageStuDlg::OnGrayLevel()
{
	//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	//����
	int level_count = 8; //����Ҷȼ���
	int step = GRAY_LEVEL_256 / level_count;
	int rule[GRAY_LEVEL_256] = { 0 };

	///���־ͱȽϿ죬��Ϊ�Ҷ�ֻ��256����ÿ���㶼����ӳ��ͺ���
	for (int i = 0; i < GRAY_LEVEL_256; ++i) {
		rule[i] = int(i / step) * step;
	}
	for (int i = 0; i < size; ++i) {
		int gray = _grayData[i];
		img[i] = rule[gray];
	}
	/*
	���ַ�ʽ������Ϊ ���ص�*2�������ص�̶������»�Ƚ��������Կ��Կռ任ʱ��
	for (int i = 0; i < size; ++i) {
		int gray = _grayData[i];
		img[i] = int(gray / step) * step;
	}
	*/
	//��ʾ
	ShowPicByArray(img, width, height);
	//ɾ����Դ
	if (img != NULL)
		delete[] img;

}

void CImageStuDlg::OnGrayLevelColorfulVersion()
{
	//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[width * height];

	//����
	int level_count = 8; //����Ҷȼ���
	int COLOR_LEVEL = 256;
	int step = COLOR_LEVEL / level_count;

	//���ַ�ʽ������Ϊ ���ص�*2�������ص�̶������»�Ƚ��������Կ��Կռ任ʱ��
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
	//��ʾ
	ShowPicByArray(img, width, height);
	//ɾ����Դ
	if (img != NULL)
		delete[] img;
}


void CImageStuDlg::OnMirrorHorizontally()
{
	//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// ˮƽ����
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			//�Գ�����
			int oldX = width - 1 - x;
			int oldY = y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//��ʾ
	ShowPicByArray(img, width, height);
	//ɾ����Դ
	if (img != NULL)
		delete[] img;

}

void CImageStuDlg::OnMirrorVertically()
{
	//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// ��ֱ����
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = y * width + x;
			//�Գ�����
			int oldX = x;
			int oldY = height - 1 - y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//��ʾ
	ShowPicByArray(img, width, height);
	//ɾ����Դ
	if (img != NULL)
		delete[] img;
}

void CImageStuDlg::OnTransposition()
{
	//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	// ת��
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = x * height + y;
			//�Գ�����
			int oldX = width - x;
			int oldY =  y;
			int oldIndex = oldY * width + oldX;
			int oldGray = _grayData[oldIndex];
			img[index] = oldGray;
		}
	}
	//��ʾ
	ShowPicByArray(img, height, width);
	//ɾ����Դ
	if (img != NULL)
		delete[] img;
}



//ǰ��ӳ��
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

//�������Բ�ֵ
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

//�Ҷ�ȡ��
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

//�����任
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

//�ݴα任
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

//��ƽ��
void CImageStuDlg::OnJunpinghua()
{
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int *img = new int[size];

	//����ӳ�����
	int rule[GRAY_LEVEL_256] = { 0 };

	//ֱ��ͼ
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
	//��һ��
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
	// �ۻ�
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

//����ƽ��
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
			//ȡ�������
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

//����������
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
			//ȡ�������
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

//��Ȩƽ��
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
			//ȡ����
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				for (int n = y - radius; n <= y + radius; ++n) {
					int oldIndex = n * width + m;
					neighbor[order++] = _grayData[oldIndex];

				}
			}
			//���
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


//��������ƽ��
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

//���ټ�Ȩƽ��
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
			horizontal[horizontal_index] = sum / 38/*Ȩֵ�������*/;
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

//2D��ֵ(��Χ)
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
			//ȡ����
			int order = 0;
			for (int m = x - radius; m <= x + radius; ++m) {
				for (int n = y - radius; n <= y + radius; ++n) {
					int oldIndex = n * width + m;
					neighbor[order++] = _grayData[oldIndex];
				}
			}
			//����
			std::stable_sort(neighbor, neighbor + neighborsz);
			//��ֵ
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
			//ȡ����(ʮ��
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
			//����
			std::stable_sort(neighbor, neighbor + neighborsz);
			//��ֵ
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
			//ȡ����(����
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
			//����
			std::stable_sort(neighbor, neighbor + neighborsz);
			//��ֵ
			img[index] = neighbor[neighborsz / 2];
		}
	}

	ShowPicByArray(img, width, height);

	if (img != NULL)
		delete[] img;
}

//������˹����
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
		// ��һ��
		double red= info.GetRed();
		double green = info.GetGreen();
		double blue = info.GetBlue();

		if (red == green && red == blue) {
			img[index] = CBaseColorInfo(0, 0, red);
		}
		else {
			// ����S
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

			//����H
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
	// TODO: �ڴ���������������
		//����ͼ��
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo* img = new CBaseColorInfo[size];

	const double PI = 3.1415926;
	const double PI_2 = 2 * PI;

	//����
	for (int x = 0; x < size; ++x) {
		//r, g, b -->hsi
		CBaseColorInfo info = _colorData[x];
		// ��һ��
		double r = info.GetRed() / 255.0;
		double g = info.GetGreen() / 255.0;
		double b = info.GetBlue() / 255.0;

		//����
		double i = (r + g + b) / 3.0;
		double h = 0.0;
		double s = 0.0;
		if (info.GetRed() == info.GetBlue() && info.GetGreen() == info.GetBlue()) {
			//�Ҷ�ͼ
			h = 0.0;
			s = 0.0;
		}
		else {
			//����s
			//1�������Сֵ
			double min = r;
			if (min > g) {
				min = g;
			}
			if (min > b) {
				min = b;
			}
			s = 1 - 3 * (min / (r + g + b));

			//����h
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

		//���Ͷ�
		//s = 0;

		//����
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
		//����ӳ�䵽[0, 255]
		img[x] = CBaseColorInfo(r, g, b);
	}
	//��ʾ
	ShowPicByArray(img, width, height);

	//ɾ��
	if (img != NULL) 
		delete[] img;
	
}
