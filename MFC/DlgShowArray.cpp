// DlgShowArray.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "DlgShowArray.h"

#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShowArray dialog


CDlgShowArray::CDlgShowArray(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowArray::IDD, pParent), _biBitCount(24), _lpBuf(0)
{
	//{{AFX_DATA_INIT(CDlgShowArray)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShowArray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowArray)
	DDX_Control(pDX, IDC_STATIC_POS, _staticPos);
	DDX_Control(pDX, IDC_COMBO_TYPE, _comboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowArray, CDialog)
	//{{AFX_MSG_MAP(CDlgShowArray)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(ID_BUTTON_SAVE, OnButtonSave)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShowArray message handlers


/************************************************************************/
/*                        ��Ϣӳ��                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// ���ƶԻ���, ӳ��WM_PAINT��Ϣ
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	CDC *pDC = GetDC();


	// ����ͼ��
// 	for( int x = 0; x <= _width - 1; x++ ){
// 		for( int y = 0; y <= _height - 1; y++ ){
// 
// 			int index = y * _width + x;
// 
// 			int curColor = 0;
// 			switch( _colorType ){
// 			case ALL:
// 				break;
// 			case RED:
// 				curColor = _colorData[ index ].GetRed();
// 				break;
// 			case GREEN:
// 				curColor = _colorData[ index ].GetGreen();
// 				break;
// 			case BLUE:
// 				curColor = _colorData[ index ].GetBlue();
// 				break;
// 			}
// 			int red = ( _colorType == ALL || _colorType == RED ) ? _colorData[ index ].GetRed() : curColor;
// 			int green = ( _colorType == ALL || _colorType == GREEN ) ? _colorData[ index ].GetGreen() : curColor;
// 			int blue = ( _colorType == ALL || _colorType == BLUE ) ? _colorData[ index ].GetBlue() : curColor;
// 			//pDC->SetPixel( x , y + _headPosRect.Height() , RGB( red, green, blue ) );
// 			
// 		}
// 	}
//	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
//	if (dlg.DoModal()==IDOK)
//	{
		// �����24λ��ɫBMPͼ��
		SaveAsBmp( (LPTSTR)(LPCTSTR)"C:/biMap/10.bmp", _lpBuf, _width, _height, 24,
			NULL );
//	}







    CString filter = L"�����ļ�(*.bmp,*.jpg,*.tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp|JPG(*.jpg)|*.jpg|GIF(*.gif)|TIFF(*.tiff)|*.tiff";
//	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (1){
		CString fPath = "C:/biMap/10.bmp";       // ��ȡ�ļ�·��
	//	CString fEnt = Ofile.GetFileExt();         // ��ȡ�ļ���չ��
	//	fEnt.MakeLower();                          // ���ļ���չ��ת��ΪСд��ĸ

		if (1){        // ����򿪵���bmp�ļ�
			// ��������洢ͼƬ��Ϣ
			BITMAPINFO *pBmpInfo;          // ��¼ͼ����Ϣ
			BYTE *pBmpData;                // ͼ������
			BITMAPFILEHEADER bmpHeader;    // �ļ�ͷ
			BITMAPINFOHEADER bmpInfo;      // ��Ϣͷ
			CFile bmpFile;                 // ��¼���ļ�

			// ��ֻ���ķ�ʽ���ļ� ��ȡbmpͼƬ������bmp���ļ�ͷ����Ϣ������
			if (!bmpFile.Open(fPath, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			
			// Ϊͼ����������ռ�
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];
			bmpFile.Read(pBmpData, dataBytes);
			bmpFile.Close();

			// ��ʾͼ��
			CWnd *pwnd = GetDlgItem(IDC_PICTURE);
			CRect rect;
			pwnd->GetClientRect(&rect);
			CDC *pDC = pwnd->GetDC();        // ��ȡpicture�ؼ����ڵ�λ��
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, _width, _height, 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
			ReleaseDC( pDC );
		}

	}














//	ReleaseDC( pDC );
	
	// Do not call CDialog::OnPaint() for painting messages
}


//////////////////////////////////////////////////////////////////////////
// ��ʼ���Ի���, ӳ��WM_INITDIALOG��Ϣ
//////////////////////////////////////////////////////////////////////////
BOOL CDlgShowArray::OnInitDialog() 
{
	CString csPath(TEXT("C:\\biMap"));
	
	if (!PathIsDirectory(csPath))	
	{
		CreateDirectory(csPath, 0);//�������򴴽�
	}


	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	_staticPos.GetWindowRect( &_headPosRect );
	ScreenToClient( &_headPosRect );
	
	// ���ô���Ĵ�С
	int showWidth = _width + 20;
	if( showWidth < _headPosRect.Width() ){
		showWidth = _headPosRect.Width();
	}

	// ����λ����Ļ���� 
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	CRect rect;
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ) ) / 2 ;
	height = ( height - (rect.bottom - rect.top ) ) / 2 ;
	

	this->SetWindowPos( NULL, width, height, showWidth, _height + _headPosRect.Height() + 50, SWP_SHOWWINDOW );
	// ��ʼ������������
	InitComboType();
	// ת����24λ��ɫλͼ
	Init24BMP();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////
// ���ٴ��壬ӳ��WM_DESTORY��Ϣ
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
	// �ͷ�λͼ����
	free( _lpBuf );
	
}

//////////////////////////////////////////////////////////////////////////
// ѡ������������(IDC_COMBO_TYPE)
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	int index = _comboType.GetCurSel();
	if( index == 0 ){
		_colorType = ALL;
	}
	else if( index == 1 ){
		_colorType = RED;	
	}
	else if( index == 2 ){
		_colorType = GREEN;	
	}
	else if( index == 3 ){
		_colorType = BLUE;	
	}

	// ˢ��24BMPͼ������
	Refresh24BMP();

	Invalidate();
}


//////////////////////////////////////////////////////////////////////////
// "����"��ť
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		// �����24λ��ɫBMPͼ��
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _width, _height, 24,
			NULL );
	}
}


/************************************************************************/
/*                         �ֶ�����                                     */
/************************************************************************/
// ͼ������
void CDlgShowArray::SetColorData( CBaseColorInfo * colorData ){
	_colorData = colorData;
}
// ͼ���С
void CDlgShowArray::SetWidth( int width ){
	_width = width;
}
void CDlgShowArray::SetHeight( int height ){
	_height = height;
}

/************************************************************************/
/*                          ˽�к���                                    */
/************************************************************************/

// ��ʼ������������
void CDlgShowArray::InitComboType(){

	_comboType.InsertString( ALL, "ȫ��" );
	_comboType.InsertString( RED, "��ɫͨ��" );
	_comboType.InsertString( GREEN, "��ɫͨ��" );
	_comboType.InsertString( BLUE, "��ɫͨ��" );
	_comboType.SetCurSel( 0 );
	_colorType = ALL;

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
bool CDlgShowArray::SaveAsBmp( char * bmpName, 
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
	//if( !fp ){
//		return false;
//	}
	
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
	head.biBitCount = biBitCount; // ������ȣ�ÿ�����ص�λ��(bit��)
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


//////////////////////////////////////////////////////////////////////////
// ��ʼ��24λBMP���ݣ���ͼ������ת��
// ��_colorData��ʾ��ͼ������(���ϵ��¡�������)ת��
//    24BMPͼ���ͼ������(���µ��ϣ������Ҵ洢)
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::Init24BMP(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _width * _biBitCount ) / 32;
	if( ( (DWORD) _width * _biBitCount ) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _width;
	int height = _height;

	// ����λͼ���ݿռ�
	if( (3 * width) % 4 == 0 ){
		_lpBuf = new BYTE[ 3 * width * height ] ;
	}
	else{
		_lpBuf = new BYTE[ dwBytes  * height ];
	}

	// �����ɫ����
	int i,j;
	
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if( (3 * width) % 4 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// ��ɫ�����е�����
			DWORD colorDataIndex = ( height - 1 - i ) * width + j;

			_lpBuf[ index  + 2 ] = _colorData[ colorDataIndex ].GetRed();
			_lpBuf[ index  + 1 ] = _colorData[ colorDataIndex ].GetGreen(  );
			_lpBuf[ index ] = _colorData[ colorDataIndex ].GetBlue();
			
		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ˢ��24λBMP���ݣ���ͼ������ת��
// ��_colorData��ʾ��ͼ������(���ϵ��¡�������)ת��
//    24BMPͼ���ͼ������(���µ��ϣ������Ҵ洢)
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::Refresh24BMP(){
	
	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _width * _biBitCount ) / 32;
	if( ( (DWORD) _width * _biBitCount ) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _width;
	int height = _height;

	
	// �����ɫ����
	int i,j;
	
	for( i = 0; i < height; i++ ){
		for( j = 0; j < width; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// ��ɫ�����е�����
			DWORD colorDataIndex = ( height - 1 - i ) * width + j;

			int curColor = 0;
			switch( _colorType ){
			case ALL:
				break;
			case RED:
				curColor = _colorData[ colorDataIndex ].GetRed();
				break;
			case GREEN:
				curColor = _colorData[ colorDataIndex ].GetGreen();
				break;
			case BLUE:
				curColor = _colorData[ colorDataIndex ].GetBlue();
				break;
			}
			int red = ( _colorType == ALL || _colorType == RED ) ? _colorData[ colorDataIndex ].GetRed() : curColor;
			int green = ( _colorType == ALL || _colorType == GREEN ) ? _colorData[ colorDataIndex ].GetGreen() : curColor;
			int blue = ( _colorType == ALL || _colorType == BLUE ) ? _colorData[ colorDataIndex ].GetBlue() : curColor;
			
			_lpBuf[ index  + 2 ] = red;
			_lpBuf[ index  + 1 ] = green;
			_lpBuf[ index ] = blue;
			
		}// for j
	}// for i 


			
	
}







