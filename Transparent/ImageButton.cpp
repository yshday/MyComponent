#include "stdafx.h"
#include "ImageButton.h"

IMPLEMENT_DYNAMIC(ImageButton, CButton)

ColorMatrix colorMatrix =
{
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

ImageButton::ImageButton()
{
	m_hover = false;
	m_tracking = FALSE;
	m_handCursor = true;

}

ImageButton::~ImageButton()
{
	for (int i = 0; i < COUNT; i++)
	{
		m_streams[i]->Release();
	}
}

BEGIN_MESSAGE_MAP(ImageButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

BOOL ImageButton::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_LBUTTONDBLCLK)
		pMsg->message = WM_LBUTTONDOWN;

	return CButton::PreTranslateMessage(pMsg);

}

void ImageButton::PreSubclassWindow()
{
	m_style = GetButtonStyle();
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);

}

void ImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect dst;
	GetClientRect(&dst);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	Graphics memDC(*pDC, dst);
	Graphics graphics(memDC.GetHDC());
	graphics.SetInterpolationMode(InterpolationModeDefault);
	graphics.SetPixelOffsetMode(PixelOffsetModeNone);

	Bitmap* bitmap = nullptr;

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		// Down
		bitmap = Bitmap::FromStream(m_streams[DOWN]);
	}
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		// Disabled
		bitmap = Bitmap::FromStream(m_streams[DISABLED]);
	}
	else if (m_hover)
	{
		// Hover
		bitmap = Bitmap::FromStream(m_streams[HOVER]);
	}
	else
	{
		// Normal
		bitmap = Bitmap::FromStream(m_streams[NORMAL]);
	}

	ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	graphics.DrawImage(bitmap, Rect(dst.left, dst.top, dst.Width(), dst.Height()), 0, 0, 50, 50, UnitPixel, &imageAttributes);

	delete bitmap;
}

void ImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_tracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 1;
		m_tracking = _TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);

}

void ImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	m_hover = true;

	if (m_handCursor)
	{
		SetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR, (LONG)AfxGetApp()->LoadStandardCursor(IDC_HAND));
	}

	Invalidate(FALSE);

	CButton::OnMouseHover(nFlags, point);

}

void ImageButton::OnMouseLeave()
{
	if (m_tracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_CANCEL;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 1;
		_TrackMouseEvent(&tme);

		m_tracking = FALSE;
	}

	m_hover = false;

	if (m_handCursor)
	{
		SetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR, (LONG)AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	Invalidate(FALSE);

	CButton::OnMouseLeave();

}

void ImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	Invalidate(FALSE);

	CButton::OnLButtonDown(nFlags, point);

}

void ImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	Invalidate(FALSE);

	CButton::OnLButtonUp(nFlags, point);

}

BOOL ImageButton::OnEraseBkgnd(CDC * pDC)
{
	return FALSE;
}

void ImageButton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	if (!bEnable)
	{
		Invalidate();
	}

}

void ImageButton::SetImage(const UINT normal, const UINT hover, const UINT down, const UINT disabled, const LPCTSTR type)
{
	auto hIns = AfxGetInstanceHandle();

	m_streams[NORMAL] = Load(MAKEINTRESOURCE(normal), type, hIns);
	m_streams[HOVER] = Load(MAKEINTRESOURCE(hover), type, hIns);
	m_streams[DOWN] = Load(MAKEINTRESOURCE(down), type, hIns);
	m_streams[DISABLED] = Load(MAKEINTRESOURCE(disabled), type, hIns);
}

IStream * ImageButton::Load(LPCTSTR name, LPCTSTR type, HINSTANCE hIns)
{
	HRSRC hResource = FindResource(hIns, name, type);
	if (!hResource)
		return nullptr;

	auto hGlobal = LoadResource(hIns, hResource);

	auto lpVoid = LockResource(hGlobal);
	if (!lpVoid)
		return nullptr;

	DWORD imageSize = SizeofResource(hIns, hResource);
	if (!imageSize)
		return nullptr;

	IStream* stream = nullptr;
	if (CreateStreamOnHGlobal(NULL, TRUE, &stream) == S_OK)
	{
		DWORD dwWritten = 0;
		if (stream->Write(lpVoid, imageSize, &dwWritten) == S_OK)
		{
			return stream;
		}
	}

	return nullptr;
}
