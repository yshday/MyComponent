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

	if (m_memDC)
	{
		//m_memDC->DrawImage(memDC, dst);
	}

	Image* image = nullptr;

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		// Down
		image = m_images[State::DOWN];
	}
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		// Disabled
		image = m_images[State::DISABLED];
	}
	else if (m_hover)
	{
		// Hover
		image = m_images[State::HOVER];
	}
	else
	{
		// Normal
		image = m_images[State::NORMAL];
	}

	ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	graphics.DrawImage(image, Rect(dst.left, dst.top, dst.Width(), dst.Height()), 0, 0, image->GetWidth(), image->GetHeight(), UnitPixel, &imageAttributes);
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
}