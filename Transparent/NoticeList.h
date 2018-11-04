#pragma once
#include <afxcmn.h>
class NoticeList : public CListCtrl
{
public:
	DECLARE_DYNAMIC(NoticeList)

	NoticeList();
	virtual ~NoticeList();

	bool SetRowHeight(const int height);

private:
	void FillRect(HDC& hdc, const RECT& rect, COLORREF color) const;
	CImageList m_imageList;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

};
