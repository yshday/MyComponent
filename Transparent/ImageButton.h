#pragma once
#include <afxwin.h>

using namespace Gdiplus;

class ImageButton : public CButton
{
	DECLARE_DYNAMIC(ImageButton)
public:
	ImageButton();
	virtual ~ImageButton();

	enum State : UINT
	{
		NORMAL,
		HOVER,
		DOWN,
		DISABLED,
		COUNT
	};


	void SetImage(const UINT normal, const UINT hover, const UINT down, const UINT disabled, const LPCTSTR type);

private:
	IStream* Load(LPCTSTR name, LPCTSTR type, HINSTANCE hIns);

	UINT m_style;
	bool m_hover;
	BOOL m_tracking;
	bool m_handCursor;

	IStream* m_streams[COUNT];

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);

};

