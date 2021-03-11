#include "stdafx.h"
#include "Image.h"
#include <atlimage.h>
#include <afxole.h>

void Image::OpenImage(CString path)
{
	CImage image;
	image.Load(path);

	COleStreamFile memStream;
	memStream.CreateMemoryStream();

	image.Save(memStream.GetStream(), Gdiplus::ImageFormatBMP);


}
